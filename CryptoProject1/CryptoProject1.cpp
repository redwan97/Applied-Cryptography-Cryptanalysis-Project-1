// CryptoProject1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Dictionary.h"
#include "LetterDistribution.h"
#include "PolyShiftDecryptor.h"
#include "Text.h"
#include "Encrypt.h"
#include "SymbolDecryptor.h"


#include <vector>
#include <string>
#include <iostream>


int main()
{	
	/*Testing using encryption function*/
	//std::string p = loadDefaultDictionary()[3];
	//p = encrypt(p);
	//p = encrypt2(p);


	std::string option;
	std::string ctext;
	std::vector<std::string> dict = loadDefaultDictionary();
	std::cout << "\t\t\t**** Applied Cryptography Project 1 ****\n" << std::endl;
	std::cout << "Authors: Redwanul (rm4243) and William (wcu201)" << std::endl;
	std::cout << "Please specify if you are checking Test 1 or Test 2, (Indicate 1 or 2): ";
	std::cin >> option;

	if (option == "Test 1" || option == "1" || option == "test 1" || option == "test1" || option == "Test1" || option == "one" || option == "t1") {
		std::cout << "For the purpose of the project, program assumes ciphertext originates from some plaintext in provided dictionary." << std::endl;
		std::cout << "Note this program can find plaintext-ciphertext pairs and only dictionary 1 has been provided to this program.\n" << std::endl;
		std::cout << "Please enter the ciphertext to be decrypted : ";
		std::cin >> ctext;
		//ctext = p;

		bool cracked = false;
		for (int i = 0; i < dict.size(); i++) {
			for (int j = 0; j < 28; j++) {
				Decryptor* dec = new MultiShiftDecryptor(i, dict[i], ctext, j + 1);
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
	}
	else if (option == "Test 2" || option == "2" || option == "test 2" || option == "test2" || option == "Test2" || option == "two" || option == "t2") {
		std::int keySize;
		std::cout << "Print whatever notes to prof you want and other details.. " << std::endl;
		std::cout << "Conducting Test 2..." << std::endl;
		std::cout << "Please enter the txt file containing the ciphertext to be decrypted : ";
		std::cin >> ctext;
		std::cout << "Please enter key length : ";
		std::cin >> keySize;
		//std::getline(std::cin, ctext);
		SymbolDecryptor* symbolDec = new SymbolDecryptor();
		symbolDec->decrypt(ctext, keySize, "plaintext_dictionary_2.txt");
		//do somehthing ..

	}
	else {
		std::cout << "Invalid Input. Exiting !!" << std::endl;
	}


    return 0;
}

