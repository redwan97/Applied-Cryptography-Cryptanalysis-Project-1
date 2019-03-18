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


int main()
{
	/* // Testing Dictionary.h file, LetterDistribution.h file, Text.h file correctness
	for (auto x : loadDefaultDictionary()) {				// for each element in dictionary that is returned by loadDefaultDict,
		Text aText(x);										//	create a Text for it
		aText.getDistribution().printFreqTable();			//	print the distribution form the text
		std::cout << std::endl;					
	}
	*/

	//partial testing of multishiftdeccryptor
	std::string p1, c1, c2, c3, p2, c4, p3, c5;
	p1 = "abcabcab";
	c1 = "bcdbcdbc";	
	c2 = "cdecdecd";    
	c3 = "bddccebd";   
	
	p2 = "bacbacba";
	c4 = "zyazyazy";

	p3 = "efghiefghiefghiefghiefghiefghiefg";
	c5 = "defghdefghdefghdefghdefghdefghdef";

	MultiShiftDecryptor m0 = MultiShiftDecryptor(0, p1, c1, 1);			// key = 'a'
	MultiShiftDecryptor m1 = MultiShiftDecryptor(0, p1, c1, 1);			// key = 'a'
	MultiShiftDecryptor m2 = MultiShiftDecryptor(0, p1, c2, 1);			// key = 'b'
	MultiShiftDecryptor m3 = MultiShiftDecryptor(0, p1, c3, 2);			// key = 'ab'
	m1.decrypt();
	m1.getExplanation();
	m2.decrypt();
	m2.getExplanation();
	m3.decrypt();
	m3.getExplanation();
	
	MultiShiftDecryptor m00 = MultiShiftDecryptor(0, p2, c4, 1);		// key = 'y'
	MultiShiftDecryptor m4 = MultiShiftDecryptor(0, p2, c4, 3);		    // key = 'yyy'
	m00.decrypt();
	m00.getExplanation();
	m4.decrypt();
	m4.getExplanation();

	MultiShiftDecryptor m5 = MultiShiftDecryptor(3, p3, c5, 5); 		// key = 'zzzzz'
	m5.decrypt();
	m5.getExplanation();

	//MultiShiftDecryptor m4 = MultiShiftDecryptor(4, p1, p2, 1);		// no key
	//MultiShiftDecryptor m5 = MultiShiftDecryptor(0, p3, c4, 1);		// different lengths, no key

	
	//if (m1.getPlainSegments()[0].getText() == "aaa") std::cout << true << std::endl;
	//else std::cout << false << std::endl;
	//if (m1.getCipherSegments()[0].getText() == "bbb") std::cout << true << std::endl;
	//else std::cout << false << std::endl;

	//if (m1.getPlainSegments()[1].getText() == "bbb") std::cout << true << std::endl;
	//else std::cout << false << std::endl;
	//if (m1.getCipherSegments()[1].getText() == "ccc") std::cout << true << std::endl;
	//else std::cout << false << std::endl;

	//if (m1.getPlainSegments()[2].getText() == "cc") std::cout << true << std::endl;
	//else std::cout << false << std::endl;
	//if (m1.getCipherSegments()[2].getText() == "dd") std::cout << true << std::endl;
	//else std::cout << false << std::endl;

	
	//m0.decrypt();
	//m00.decrypt();
	//LetterDistribution m0Sym = m0.getPlainSegments()[0].getDistribution();
	//LetterDistribution m00Sym = m00.getPlainSegments()[0].getDistribution();
	//if (m0Sym.equalByDistribution(m00Sym)) std::cout << true;


    return 0;
}

