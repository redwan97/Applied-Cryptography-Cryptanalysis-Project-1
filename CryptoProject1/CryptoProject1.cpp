// CryptoProject1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Dictionary.h"
#include "LetterDistribution.h"
#include "PolyShiftDecryptor.h"
#include "Text.h"


#include <vector>
#include <string>
#include <iostream>


int siFinder(std::string str, char c);																		//Encryption helper function
std::string encrypt(std::string s);																			//Encryption function
std::string encrypt2(std::string s);																		//Encryption function

int main()
{	
	/*Testing using encryption function*/
	//std::string p = loadDefaultDictionary()[3];
	//p = encrypt(p);
	//p = encrypt2(p);
	
	std::string ctext;
	std::vector<std::string> dict = loadDefaultDictionary();
	std::cout << "\t\t\t**** Applied Cryptography Project 1 Test1(dict1)****\n" << std::endl;
	std::cout << "Authors: Redwanul (rm4243) and William (wcu201)" << std::endl;
	std::cout << "For the purpose of the project, program assumes ciphertext originates from some plaintext in provided dictionary." << std::endl;
	std::cout << "Note this program can find plaintext-ciphertext pairs and only dictionary 1 has been provided to this program.\n" << std::endl;
	std::cout << "Please enter the ciphertext to be decrypted : ";
	std::cin >> ctext;
	
	//ctext = p;

	bool cracked = false;
	for (int i = 0; i < dict.size(); i++) {
		for (int j = 0; j < 28; j++) {
			Decryptor* dec = new MultiShiftDecryptor(i, dict[i], ctext, j+1);			
			if (dec->decrypt()) {
				std::cout << "Program's guess of plaintext is: " << dict[i] << std::endl;
				dec->getExplanation();
				cracked = true;
				delete dec;
				break;
			}
			delete dec;
		}
	}
	if (!cracked) { std::cout << "Could not decode ciphertext. Please have mercy :( " << std::endl; }
	
	/*Testing on simple plaintexts*/ 
	/*
	std::string s, c;
	s = "hi how are you dude";
	c = encrypt(s);
	bool cracked = false;
	for (int i = 0; i < 40; i++) {
		Decryptor* d =  new MultiShiftDecryptor(0, s, c, i+1);
		if (d->decrypt()) {
			d->getExplanation();
			cracked = true;
			delete d;
			break;
		}
		delete d;
	}
	if (!cracked) { std::cout << "Could not decode ciphertext. Please have mercy :( " << std::endl; }  
	*/
	

	/*Testing header file correctness*/
	/*
	for (auto x : loadDefaultDictionary()) {					// for each element in dictionary that is returned by loadDefaultDict,
		Text aText(x);											//	create a Text for it
		aText.getDistribution().printFreqTable();				//	print the distribution form the text
		std::cout << std::endl;
	}
	*/

    return 0;
}


int siFinder(std::string str, char c) {
	int ind = 0;
	for (auto x : str) {
		if (x != c) { ind++; }
		else break;
	}
	return ind;
}

std::string encrypt(std::string s) {
	const std::string alphabet = std::string("abcdefghijklmnopqrstuvwxyz ");
	std::vector<int> k;
	for (int i = 0; i < 27; i++) { k.push_back(i); }

	std::string cipher = "";
	int j;
	for (int i = 0; i < s.length(); i++) {
		j = (1 + i) % 24;
		cipher += alphabet[(siFinder(alphabet, s[i]) + k[j]) % 27];
	}
	return cipher;
}

std::string encrypt2(std::string s) {
	const std::string alphabet = std::string("abcdefghijklmnopqrstuvwxyz ");
	std::vector<int> k;
	for (int i = 0; i < 27; i++) { k.push_back(i); }

	std::string cipher = "";
	int j;
	for (int i = 0; i < s.length(); i++) {
		j = i * (1 + i) % 24;
		cipher += alphabet[(siFinder(alphabet, s[i]) + k[j]) % 27];
	}
	return cipher;
}