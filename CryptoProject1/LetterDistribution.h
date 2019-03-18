#pragma once
#ifndef LETTERDISTRIBUTION_H_
#define LETTERDISTRIBUTION_H_

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


/* LetterDistribution.h */

// This class stores the frequency of symbols in a Message. The members variables
// are the alphabet, distribution, and unique symbol count. The default alphabet 
// is the 26-lettered lowercase english alphabet. There is functionality to compare
// distributions of two messages.


																										// Terminology: Symbols = alphabets = characters
static std::string defaultSymbols = std::string("abcdefghijklmnopqrstuvwxyz ");							// Define default symbol as lowercase english alphabet

class LetterDistribution {
protected:
	std::string symbols;																				// The alphabet defines the set of symbols for distribution
	std::map<char, int> frequencyTable;																	// Frequency table to hold char-count 
	int unqSymCount;																					// Count of unique symbols in message

	static std::map<char, int> determineDistribution(const std::string& msg) {							// Calculates the symbol frequency for the message provided
		std::map<char, int> frequencyTable;																// Frequency table to be returned  
		for (std::string::const_iterator itr = msg.begin(); itr != msg.end(); ++itr) {					// Loop through message, char is key and value is frequncy (char, char count)
			frequencyTable[*itr] += 1;																	// Increment the frequency of each char as it is encoutered
		}
		return frequencyTable;																			// Return the frequency table
	}

	struct FrequencyEqualityComparator {																// Define a comparator that allows comparison between the frequency of two chars
		bool operator() (std::pair<int, char> lhs, std::pair<int, char> rhs) {
			return lhs.first == rhs.first;
		}
	};


public:
	LetterDistribution() : symbols(defaultSymbols), unqSymCount(0) {}									// Default constructor, sets symbols to default alphabet
	LetterDistribution(const std::string& msg, const std::string& alphabet = defaultSymbols) 
		: symbols(alphabet), unqSymCount(msg.length()), frequencyTable(determineDistribution(msg)) {}	// Sibiling constructor, can specify alphabet, symbolCount, and frequency table
	
	virtual ~LetterDistribution() {}

	int getSymbolCount() const { return unqSymCount; }													// Getter for SymbolCount 
	const std::string getSymbols() const { return symbols; }											// Getter for Symbols
	const int getSymbolsSize() const { return getSymbols().length(); }									// Getter for Symbol size
	bool equalBySymbols(LetterDistribution& other) { return frequencyTable == other.frequencyTable; }	// Test if frequency tables are exactly the same, == operator

	bool equalByDistribution(LetterDistribution& other) {												// Test if frequency tables are equal, return true if equal
		std::vector<std::pair<int, char>> left;															// Define List of (char count, char) pairs for this
		std::vector<std::pair<int, char>> right;														// Define List of (char count, char) pairs for other
		left = reverseFreqTable();																		// Build list for this
		right = other.reverseFreqTable();																// Build list for other
		if (left.size() != right.size()) { return false; }												// Return false if we don't have the same amount of items
		return std::equal(left.begin(), left.end(), right.begin(), FrequencyEqualityComparator());		// Test if the distribution for the two is the same using member comparator
	}

	void printFreqTable() const {
		for (auto itr = frequencyTable.begin(); itr != frequencyTable.end(); ++itr) {					// Iterate through freqTable
			std::cout << "Char: " << itr->first << ":" << itr->second << std::endl;						// Print freq pairs											
		}
	}

	std::vector<std::pair<int, char>> reverseFreqTable() const {										// Creates a freqList with reversd key,val pairs -> (char count, char)
		std::vector<std::pair<int, char>> freqList;														// Define freqList to be returned
		std::pair<int, char> symbolFrequency;															// Define instance of freq pair
		for (auto itr = frequencyTable.begin(); itr != frequencyTable.end(); ++itr) {					// Iterate through freqTable
			symbolFrequency = std::pair<int, char>(itr->second, itr->first);							// Create the reversed pair using pair constructor
			freqList.push_back(symbolFrequency);														// Add reversed pair to freqList
		}
		std::stable_sort(freqList.begin(), freqList.end());												// Stable sort the list, maintain order if freq of two symbols is same
		return freqList;																				// Return freqList, vector of pairs
	}
};

#endif 

