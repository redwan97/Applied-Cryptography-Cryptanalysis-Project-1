#pragma once

#ifndef POLYSHIFTDECRYPTOR_H_
#define POLYSHIFTDECRYPTOR_H_

#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>

#ifndef TEXT_H_
#include "Text.h"
#endif

#ifndef DECRYPTOR_H_
#include "Decryptor.h"
#endif

/* POLYSHIFTDECRYPTOR */

/*
 Use the polyalphabetic cipher decryption strategy and build on it. Requires an additional 
 parameter of key length, T,  as an input. Starts key length at 1 if not specified. Assumed 
 that the key is applied to the plain text in some regular and deterministic way that repeats
 with a period of T. Using only every i'th symbol from 0 to T-1, divide both the plain text 
 and cipher text into T segments. Treat each segment in both plain text and cipher text as 
 Text classes with their own LetterDistribution. Compare the symbol distrubution by frequency 
 only as you cycle through the segments. If the counts match up, we attempt to calculate the 
 shift for that key position by trying all symbols found to have the same frequency count 
 (using the maximum count as a starting point). We test each possible shift, by applying that 
 shift to the plain text and comparing it against the cipher text. This continues until any 
 segment or shift fails or until we succeed.
 */

class MultiShiftDecryptor : public Decryptor {
protected:
	int keyLength;																																					// Key length = 1 if input not provided
	std::vector<Text> plainSegments;																																// List of plain text segments as Messages
	std::vector<Text> cipherSegments;																																// List of plain text segments as Messages
	std::vector<int> keyShifts;																																		// List of effective shifts inferred from the decryption attempt
public:
	MultiShiftDecryptor(int index, std::string plainText, std::string cipherText, int kl = 1) 
		: Decryptor(index, plainText, cipherText), keyLength(kl) {}

	virtual ~MultiShiftDecryptor() {}
	bool decrypt() {
		if (!isInitialized) { initialize(); }																														// Initialize the Decryptor, setup plain and cipher segments
		for (int segmentIndex = 0; segmentIndex < keyLength; segmentIndex++) {																						// Iterate through plain and cipher text segments in parallel
			LetterDistribution plainDistro = plainSegments[segmentIndex].getDistribution();																			// Create distributions for current segment in plainSegments
			LetterDistribution cipherDistro = cipherSegments[segmentIndex].getDistribution();																		// Create distributions for current segment in cipherSegments
			if (!cipherDistro.equalByDistribution(plainDistro)) { return false; }																					// Check if the segments have the same set of counts by distribution
			int keyValue = determineSegmentKey(plainSegments[segmentIndex], cipherSegments[segmentIndex]);															// If segments have matching frequencies, try to determine shift value
			if (keyValue >= 0) { keyShifts.push_back(keyValue); }																									// Save valid shift values into shift list
			else { return false; }		
		}
		return true;																																				// If all segments matched then return success
	}

	int getKeyLength() const { return keyLength; }
	const std::vector<Text>& getCipherSegments() const { return cipherSegments; }
	const std::vector<Text>& getPlainSegments() const { return plainSegments; }

	// Create an explanation for how the plain text was possibly encrypted.
	// Report list of shifts and possible key phrase.
	const std::string getExplanation() const {
		std::string explanation;
		std::ostringstream os(explanation);
		std::cout << "\nFor plaintext = '" << plainText << "'" << "\n\nAnd ciphertext = '" << cipherText << "'\n\nThe following has been deduced:" << std::endl;
		if (getKeyShifts().empty()) {																																// if we don't have key shifts, we were not successful
			std::cout << "The cipher text to plain text at index " << getDictionaryIndex() << " was not a match using key length " << getKeyLength() << std::endl;
		}
		else {
			std::cout << "Decrypted cipher text found to match plain text at index " << dictionaryIndex << "." << std::endl << "This appears to be a ";				// test for a single shift repeated by building a set
			std::set<int> uniqueShifts(getKeyShifts().begin(), getKeyShifts().end());																				// only 1 shift value repeated T times
			if (uniqueShifts.size() == 1) {
				char keySymbol = *(uniqueShifts.begin()) + plainSegments[0].getDistribution().getSymbols()[0] - 1;
				if (keySymbol == '`') { keySymbol = ' '; }																											// more hardcoded magic
				std::cout << "simple shift cipher using a shift of " << *uniqueShifts.begin() << " or '" << keySymbol << "'." << std::endl;
			}
			else {																																					// multiple shift values. Report these and get the key string.
				std::cout << "polyalphabetic shift cipher with effective shift sequence of '" << getKeyString() << "'." << std::endl;
			}
		}
		std::cout << std::endl;
		return std::string(os.str());
	}

	const std::vector<int>& getKeyShifts() const { return keyShifts; }																								// Returns the effective shifts used for encryption. Effective meaning the key that looks like it was used for encryption. Obviously the actual key could be a result of a detrministic function used to select a shift value from the key

	const std::string getKeyString() const {																														// Build a string from keyShifts 
		std::string keyString;
		for (auto it = keyShifts.begin(); it != keyShifts.end(); ++it) {
			char keySymbol = *it + plainSegments[0].getDistribution().getSymbols()[0] - 1;
			if (keySymbol == '`') { keySymbol = ' '; }																												// Same hardcoded magic as earlier
			keyString += keySymbol;
		}
		return keyString;
	}

protected:
	void initialize() {																																				// Initilize, set flag to true and set plain and cipher segments
		plainSegments = deriveSegments(plainText, keyLength);																										// Derive plainText segment
		cipherSegments = deriveSegments(cipherText, keyLength);																										// Derive cipherText segment
		isInitialized = true;
	}

	static std::vector<Text> deriveSegments(std::string text, int keyLength) {																						// Derive segments from the provided text, returning a list with one segment per key position dictated by the key length. Each segment is represented as a Text.
		int textLength = text.length();
		//int segmentMax = ceil((float)textLength / keyLength) + 1;																									// Determine the longest segment to set the segment buffer size
		//char segments[keyLength][segmentMax];
		std::vector<std::vector<char>> segments;
		for (int i = 0; i < keyLength; i++) segments.push_back(std::vector<char>());
		for (int textIndex = 0; textIndex < textLength; textIndex++) {																								// Make one pass through the input text, appending each symbol to the proper segment
			int segment = textIndex % keyLength;
			int segmentIndex = floor(textIndex / keyLength);
			//segments[segment][segmentIndex] = text[textIndex];
			segments[segment].push_back(text[textIndex]);
			//segments[segment][segmentIndex + 1] = '\0';
		}		
		std::vector<Text> messages;																																	// Walk through the completed segments, creating a Message for each and appending it to the list
		for (int segmentIndex = 0; segmentIndex < keyLength; segmentIndex++) {
			if (!segments[segmentIndex].empty()) {
				std::string s = "";
				for (auto x : segments[segmentIndex]) { s += x; }
				//messages.push_back(Text(std::string(segments[segmentIndex])));
				messages.push_back(Text(s));
			}
		}
		return messages;
	}

	struct FrequencyOrderComparator {																																// Comparator for ordering <int, char> pairs on int 
		bool operator() (const std::pair<int, char>& lhs, const std::pair<int, char>& rhs) {
			return lhs.first < rhs.first;
		}
	};
	
	
	// Given two segments, try to find shift from plain to cipher. Do this by taking the most  
	// frequenct cipher text symbol and finding all symbols with equal count from cipher and 
	// plain text. Treat each of these symbols as potential shifts to transform the plain text 
	// to the cipher text. Test each possibility by simulating the shift from plain to cipher 
	// text and testing for equality with the cipher text.

	static int determineSegmentKey(Text& plainMessage, Text& cipherMessage) {
		std::vector<std::pair<int, char>> plainFreqs = plainMessage.getDistribution().reverseFreqTable();															// For plain text, get distribution with reverse freq table (int, char)	
		std::vector<std::pair<int, char>> cipherFreqs = cipherMessage.getDistribution().reverseFreqTable();															// For cipher text, get distribution with reverse freq table (int, char)	
		std::pair<int, char> cipherMostFrequentSymbol = cipherFreqs.back();																							// Find most frequent cipher text symbol (we need to start some place)

		auto cipherMaxSymbolRange = std::equal_range(cipherFreqs.begin(), cipherFreqs.end(),cipherMostFrequentSymbol, FrequencyOrderComparator());					// Find all symbols with same count in cipher and plain text segments
		auto plainMaxSymbolRange = std::equal_range(plainFreqs.begin(), plainFreqs.end(),cipherMostFrequentSymbol, FrequencyOrderComparator());
		
		int alphabetSize = plainMessage.getDistribution().getSymbolsSize();
		for (auto cipherSymbol = cipherMaxSymbolRange.first; cipherSymbol != cipherMaxSymbolRange.second; ++cipherSymbol) {											// Check each plain-cipher combination of equal frequency symbols to identify possible shifts
			for (auto plainSymbol = plainMaxSymbolRange.first; plainSymbol != plainMaxSymbolRange.second; ++plainSymbol) {
				int shift = ((cipherSymbol->second - plainSymbol->second) + alphabetSize) % alphabetSize;
				std::string shiftedPlain = plainMessage.getShiftedText(shift);																						// Simulate shift of plain text
				if (cipherMessage.getText() == shiftedPlain) { return shift; }																						// Compare to cipher text
			}
		}
		return -1;																																					// Return -1 if no matches
	}
};
#endif