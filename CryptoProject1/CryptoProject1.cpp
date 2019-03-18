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

		//if (i % 3 == 1) { j = 1;  }
		//else if (i % 3 == 2) { j = 2; }
		//else { j = 3; }
		//std::cout << k[j] << " ";

		cipher += alphabet[(siFinder(alphabet, s[i]) + k[j])%27];
	}
	std::cout << std::endl;

	return cipher;

}

int main()
{	
	
	//std::string p = loadDefaultDictionary()[1];
	//std::cout << p.length() << std::endl;

	//p = encrypt(p);
	//std::cout << p.length() << std::endl;
	//std::cout << p << std::endl << "\n";

	std::string ctext;
	std::vector<std::string> dict = loadDefaultDictionary();
	std::cout << "**** Applied Cryptography Project 1 part 1 by William and Redwanul ****" << std::endl;
	std::cout << "Please enter the ciphertext to be decrypted : ";
	std::cin >> ctext;
	
	//ctext = p;

	bool cracked = false;
	for (int i = 0; i < dict.size(); i++) {
		for (int j = 0; j < 28; j++) {
			MultiShiftDecryptor* dec = new MultiShiftDecryptor(i, dict[i], ctext, j+1);			
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
	
	
	//Test
	/*
	std::string s, c;
	s = "hi how are you";
	c = encrypt(s);
	for (int i = 0; i < 5; i++) {
		Decryptor* d =  new MultiShiftDecryptor(0, s, c, i+1);
		if (d->decrypt()) {
			d->getExplanation();
			delete d;
			break;
		}
		delete d;
	}
	*/

    return 0;
}



/* 
// Testing Dictionary.h file, LetterDistribution.h file, Text.h file correctness
for (auto x : loadDefaultDictionary()) {				// for each element in dictionary that is returned by loadDefaultDict,
	Text aText(x);										//	create a Text for it
	aText.getDistribution().printFreqTable();			//	print the distribution form the text
	std::cout << std::endl;
}
*/

/*
//partial testing of multishiftdeccryptor
std::string p0, c0, p1, c1, c2, c3, p2, c4, p3, c5;
p1 = "abcabcab";
c1 = "bcdbcdbc";
c2 = "cdecdecd";
c3 = "bddccebd";

p2 = "bacbacba";
c4 = "zy zy zy"; //c to a

p3 = "efghiefghiefghiefghiefghiefghiefg";
c5 = "defghdefghdefghdefghdefghdefghdef";

p0 = "hey you";
c0 = "ifzazpv";
//MultiShiftDecryptor mx = MultiShiftDecryptor(0, p0, c0, 1);
//mx.decrypt();
//mx.getExplanation();

//MultiShiftDecryptor m0 = MultiShiftDecryptor(0, p1, c1, 1);			// key = 'a'
//MultiShiftDecryptor m1 = MultiShiftDecryptor(0, p1, c1, 1);			// key = 'a'
//MultiShiftDecryptor m2 = MultiShiftDecryptor(0, p1, c2, 1);			// key = 'b'
for (int i = 0; i < c3.size(); i++) {
	MultiShiftDecryptor m3 = MultiShiftDecryptor(0, p1, c3, i+1);		// key = 'ab'
	if (m3.decrypt()) {
		m3.getExplanation();
		break;
	}
}
//m1.decrypt();
//m1.getExplanation();
//m2.decrypt();
//m2.getExplanation();


//MultiShiftDecryptor m00 = MultiShiftDecryptor(0, p2, c4, 1);		// key = 'x'
//MultiShiftDecryptor m4 = MultiShiftDecryptor(0, p2, c4, 3);		// key = 'xxx'
//m00.decrypt();
//m00.getExplanation();
//m4.decrypt();
//m4.getExplanation();

//MultiShiftDecryptor m5 = MultiShiftDecryptor(3, p3, c5, 5); 		// key = 'yyyyy'
//m5.decrypt();
//m5.getExplanation();
*/
