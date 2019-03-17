#pragma once

#ifndef DECRYPTOR_H_
#define DECRYPTOR_H_

#include <vector>
#include <string>

/* Decryptor */

// Decryptor is the base abstract class for all decrypting methods
// Different decryption strategies will extend this class
// The class defines an interface for ciphertext decryption
// The decrypt() function will return true on successful decryption 
// Index of correct plaintext can be retrieved
// Possible explanation that details encryption/decryption methods may be provided

class Decryptor {
protected:
	void initialize() { isInitialized = true; }														// Marks decryptor ready for use
	int dictionaryIndex = -1;																		// Dictionary Index, starts at an invalid -1
	bool isInitialized = false;																		// Default isIntiliaze flag to false
	std::string plainText;																			// Plaintext candidate
	std::string cipherText;																			// Ciphertext to be decrypted

public:
	Decryptor(int index, std::string pText, std::string cText)
		: dictionaryIndex(index), plainText(pText), cipherText(cText), isInitialized(false) {}		// Decryptor constructor

	virtual ~Decryptor() {}
	virtual bool decrypt() = 0;																		// Abstract decrypt function, will be implemented by child class
	virtual const std::string getExplanation() const = 0;											// Abstratct explanation function, will be implemented by child class

	const std::string& getPlainText() const { return plainText; }									// Getter for PlainText
	const std::string& getCipherText() const { return cipherText; }									// Getter for CipherText
	int getDictionaryIndex() const { return dictionaryIndex; }										// Getter for DictionaryIndex	
};

#endif