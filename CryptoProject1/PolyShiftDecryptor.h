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

// Use the polyalphabetic cipher decryption strategy and build on it
// Requires an additional parameter of key length, T,  as an input 
// Starts key length at 1 if not specified 
// Assumed that the key is applied to the plain text in some regular 
// and deterministic way that repeats with a period of T
// The basic strategy is to divide the plain and cipher text into T segments
// using only every Jth symbol from 0 to T-1. Each of these segments from the
// plain and cipher texts is treated as a separate Message, each with its own
// LetterDistribution. We then cycle through the segments, comparing the symbol
// distributions by frequency only. If the counts match up, we attempt to
// calculate the shift for that key position by trying all symbols found to have
// the same frequency count (using the maximum count as a starting point). We
// test each possible shift, by applying that shift to the plain text and
// comparing it against the cipher text. This continues until any segment or
// shift fails or until we succeed.


class MultiShiftDecryptor : public Decryptor {
public:

	MultiShiftDecryptor(int index, std::string plainText, std::string cipherText, int kl = 1) 
		: Decryptor(index, plainText, cipherText), keyLength(kl) {}

	virtual ~MultiShiftDecryptor() {}

	/**
	* Attempt to match the cipher text to the challenge text using the
	* following strategy:
	*
	*   1. Divide the plain and cipher text into T segments using only every
	*     c*t+j symbol from c from 0 to L/t-1. Each of these segments from
	*     the plain and cipher texts is treated as a separate Message, each
	*     with its own SymbolDistribution.
	*   2. Cycle through the segments, comparing the symbol distributions by
	*     frequency only.
	*   3. If the counts match up, we attempt to calculate the shift for that
	*     key position. Start with the most frequent symbol and try all symbols
	*     found to have the same frequency count.
	*   4. Test each possibly shift by applying that shift to the plain text and
	*     comparing it against the cipher text.
	*   5. Continue until any segment or shift fails or until we succeed.
	*
	*/
	bool decrypt() {
		if (!isInitialized) { initialize(); }																	// initialize the Decryptor
		for (int segmentIndex = 0; segmentIndex < keyLength; segmentIndex++) {									// iterate through plain and cipher text segments in parallel
			LetterDistribution plainDistro = plainSegments[segmentIndex].getDistribution();
			LetterDistribution cipherDistro = cipherSegments[segmentIndex].getDistribution();
			if (!cipherDistro.equalByDistribution(plainDistro)) { return false; }								// check if the segments have the same set of counts (ignoring symbols for those counts)
			int keyValue = determineSegmentKey(plainSegments[segmentIndex], cipherSegments[segmentIndex]);		// for segments with matching frequencies, attempt to determine shift value
			if (keyValue >= 0) { keyShifts.push_back(keyValue); }												// save valid shift values into shift list
			else { return false; }		
		}

		// all segments matched, return success
		return true;
	}

	const std::vector<Text>& getCipherSegments() const { return cipherSegments; }
	int getKeyLength() const { return keyLength; }
	const std::vector<Text>& getPlainSegments() const { return plainSegments; }

	/**
	* Compile a statement explaining how the plain text was encrypted into the
	* cipher text. If the key is the same shift repeated, assume this is
	* actually a simple shift with a deceptive key length. Otherwise report
	* the list of shifts and the possible key phrase (using the alphabet from
	* the SymbolDistribution)
	* @return std::string - explanatory message
	*/
	const std::string getExplanation() const {
		std::string explanation;
		std::ostringstream os(explanation);
		// if we don't have key shifts, we were not successful
		if (getKeyShifts().empty()) {
			os << "The cipher text to plain text at index " << getDictionaryIndex() << " was not a match using key length " << getKeyLength() << std::endl;
		}
		else {
			os << "Decrypted cipher text found to match plain text at index " << dictionaryIndex << ". This appears to be a ";		
			// test for a single shift repeated by building a set
			std::set<int> uniqueShifts(getKeyShifts().begin(), getKeyShifts().end());
			// only 1 shift value repeated T times
			if (uniqueShifts.size() == 1) {
				char keySymbol = *(uniqueShifts.begin()) + plainSegments[0].getDistribution().getSymbols()[0];
				os << "simple shift cipher using a shift of " << *uniqueShifts.begin() << " or '" << keySymbol << "'.";
			}
			else {
				// multiple shift values. Report these and get the key string.
				os << "polyalphabetic shift cipher with effective shift sequence of " << /*getKeyShifts()*/ " or '" << getKeyString() << "'.";
			}
		}
		return std::string(os.str());
	}

	/**
	* Return the list of effective shifts in key order. "Effective" refers to
	* the fact that this is how the shifts appear based on the decryption
	* success. The actual key used to encrypt could be different as a result
	* of the function used to select a shift value from the key.
	* @return std::vector<int> - list of effective shifts
	*/
	const std::vector<int>& getKeyShifts() const { return keyShifts; }

	/**
	* Return the list of effective shifts by treating each shift as a symbol
	* value in the specified alphabet. "Effective" refers to the fact that
	* this is how the shifts appear based on the decryption success. The
	* actual key used to encrypt could be different as a result of the function
	* used to select a shift value from the key.
	* @return std::string - effective key string
	*/
	const std::string getKeyString() const {
		std::string keyString;
		for (std::vector<int>::const_iterator it = keyShifts.begin(); it !=
			keyShifts.end(); ++it) {
			char keySymbol = *it + plainSegments[0].getDistribution().getSymbols()[0];
			keyString += keySymbol;
		}
		return keyString;
	}

protected:
	int keyLength;																								// key length provided on input
	std::vector<Text> plainSegments;																			// list of plain text segments as Messages
	std::vector<Text> cipherSegments;																			// list of plain text segments as Messages
	std::vector<int> keyShifts;																					// list of effective shifts inferred from the decryption attempt

	void initialize() {																							// Initlize, set flag to true and set plain and cipher segments
		plainSegments = deriveSegments(plainText, keyLength);													// Derive plainText segment
		cipherSegments = deriveSegments(cipherText, keyLength);													// Derive cipherText segment
		isInitialized = true;
	}

	/**
	* Derive segments from the provided text, returning a list with one segment
	* per key position dictated by the key length. Each segment is represented
	* as a Message.
	* @param text - string text to segment
	* @param keyLength - integer length of key and number of segments
	* @return std::vector<Message> - list of segments as Messages
	*/
	static std::vector<Text> deriveSegments(std::string text, int keyLength) {
		int textLength = text.length();
		int segmentMax = ceil((float)textLength / keyLength) + 1;												// determine the longest segment to set the segment buffer size
		//char segments[keyLength][segmentMax];
		std::vector<std::vector<char>> segments;

		for (int textIndex = 0; textIndex < textLength; textIndex++) {											// make one pass through the input text, appending each symbol to the proper segment
			int segment = textIndex % keyLength;
			int segmentIndex = floor(textIndex / keyLength);
			segments[segment][segmentIndex] = text[textIndex];
			//segments[segment][segmentIndex + 1] = '\0';
		}		
		std::vector<Text> messages;																				// walk through the completed segments, creating a Message for each and appending it to the list
		for (int segmentIndex = 0; segmentIndex < keyLength; segmentIndex++) {
			std::string s = "";
			for (auto x : segments[segmentIndex]) { s += x; }
			//messages.push_back(Text(std::string(segments[segmentIndex])));
			messages.push_back(Text(s));
		}
		return messages;
	}

	/**
	* Inner utility class for ordering <int, char> pairs based solely on the
	* integer and ignoring the symbol.
	*/
	struct FrequencyOrderComparator {
		bool operator() (const std::pair<int, char>& lhs, const std::pair<int, char>& rhs) {
			return lhs.first < rhs.first;
		}
	};

	/**
	* For two segments, attempt to determine the shift that would produce the
	* cipher text from the plain text. Do this by taking the most frequent
	* cipher text symbol and finding all symbols with equal count from cipher
	* and plain text. Treat each of these symbols as potential shifts to
	* transform the plain text to the cipher text. Test each possibility by
	* simulating the shift from plain to cipher text and testing for equality
	* with the cipher text.
	* @param plainMessage - Message representing the plain text
	* @param cipherMessage - Message representing the cipher text
	* @return int - positive shift value required to transform plain text to
	* cipher text. -1 if no shift found.
	*/
	static int determineSegmentKey(Text &plainMessage, Text &cipherMessage) {

		// invert distributions to get <int, char> pairs of counts per symbol
		std::vector<std::pair<int, char>> plainFreqs = plainMessage.getDistribution().reverseFreqTable();
		std::vector<std::pair<int, char>> cipherFreqs = cipherMessage.getDistribution().reverseFreqTable();

		// find most frequent cipher text symbol (we need to start some place)
		std::pair<int, char> cipherMostFrequentSymbol = cipherFreqs.back();

		// find all symbols with same count in cipher and plain text segments
		std::pair<std::vector<std::pair<int, char> >::iterator, 
			      std::vector<std::pair<int, char> >::iterator> cipherMaxSymbolRange =
		std::equal_range(cipherFreqs.begin(), cipherFreqs.end(),cipherMostFrequentSymbol, FrequencyOrderComparator());
		
		std::pair<std::vector<std::pair<int, char> >::iterator,
				  std::vector<std::pair<int, char> >::iterator> plainMaxSymbolRange =
		std::equal_range(plainFreqs.begin(), plainFreqs.end(),cipherMostFrequentSymbol, FrequencyOrderComparator());

		// check each plain-cipher combination of equal frequency symbols to
		// identify possible shifts
		int alphabetSize = plainMessage.getDistribution().getSymbolsSize();
		for (std::vector<std::pair<int, char> >::iterator cipherSymbol =
			cipherMaxSymbolRange.first;
			cipherSymbol != cipherMaxSymbolRange.second; ++cipherSymbol) {
			for (std::vector<std::pair<int, char> >::iterator plainSymbol =
				plainMaxSymbolRange.first;
				plainSymbol != plainMaxSymbolRange.second; ++plainSymbol) {
				int shift = ((cipherSymbol->second - plainSymbol->second) + alphabetSize) % alphabetSize;

				// simulate shift of plain text
				std::string shiftedPlain = plainMessage.getShiftedText(shift);

				// compare to cipher text
				if (cipherMessage.getText() == shiftedPlain) { return shift; }
			}
		}

		// no matches
		return -1;
	}
};
#endif