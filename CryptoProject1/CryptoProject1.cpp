// CryptoProject1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Dictionary.h"
#include "LetterDistribution.h"
#include "Text.h"


#include <vector>
#include <string>
#include <iostream>


int main()
{
	// /*Testing Dictionary.h file, LetterDistribution.h file, Text.h file correctness
	for (auto x : loadDefaultDictionary()) {				// for each element in dictionary that is returned by loadDefaultDict,
		Text aText(x);										//	create a Text for it
		aText.getDistribution().printFreqTable();			//	print the distribution form the text
		std::cout << std::endl;					
	}
	// */



    return 0;
}

