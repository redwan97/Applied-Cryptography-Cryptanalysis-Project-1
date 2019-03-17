#pragma once


#ifndef TEXT_H_
#define TEXT_H_

#include <string>
#include <map>
#include "LetterDistribution.h"

/* Text.h */

// This class is a wrapper of the letterDistribution as it can hold both cipher and plain texts.
// Allows for some extra functionality such as getting a shifted text by some character ch

class Text {
protected:
	std::string text;																										// The text itself
	LetterDistribution distribution;																						// Distribution for the text
public:
	Text(std::string text, std::string& alphabet = defaultSymbols)															
		: text(text), distribution(LetterDistribution(text, alphabet)) {}													// On construction, specify text and create distribution for text
	virtual ~Text() {};																										// Destructor
	const LetterDistribution& getDistribution() const { return distribution; }												// Getter for distribution
	const std::string& getText() const { return text; }																		// Getter for text content
	void setText(const std::string &text, std::string &alphabet = defaultSymbols) {											// Setter for text, determines new distribution as well
		this->text = text;
		distribution = LetterDistribution(text, alphabet);
	}

	//Shifts a copy of text by shift units to the left or right
	std::string getShiftedText(int shift) const {
		std::string shiftedText = "";																						// Text string to be returned, initially empty
		int symbolsSize = getDistribution().getSymbolsSize();																// Find size of used symbols
		char symbolsBase = getDistribution().getSymbols()[0];																// Find base of used symbols
		char shiftedSymbol;																									// Holder for each shifted char

		for (auto it = text.begin(); it != text.end(); ++it) {																// For each char in plaintext
			shiftedSymbol = getDistribution().getSymbols()[((*it - symbolsBase) + (symbolsSize + shift)) % symbolsSize];	// Determine shifted char
			shiftedText += shiftedSymbol;																					// Add shifted char to shifted text
		}
		return shiftedText;																									// Return ShiftedText
	}
};
#endif 