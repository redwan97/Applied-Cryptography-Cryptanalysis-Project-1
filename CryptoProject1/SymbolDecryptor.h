#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

class SymbolDecryptor {
	private:
		map<char, int> shifts;
		map<int, char> shiftsToChars;
		vector< vector<int> >comb;
		vector<int> defaultKey;
		map<string, int> plaintextDictionary;
		bool decryptionSuccess = false;

	public:

		//extern std::vector< vector<int> > pe;


		void combinations(vector<vector<int> > array, int i, vector<int> accum){
			
		    if (i == array.size()) // done, no more rows
		    {
		        comb.push_back(accum); // assuming comb is global
		    }
		    else
		    {
		        vector<int> row = array[i];
		        for(int j = 0; j < row.size(); ++j)
		        {
		            vector<int> tmp(accum);
		            tmp.push_back(row[j]);
		            combinations(array,i+1,tmp);
		        }
		    }

		   
		}

		void mapDictionary(){
			string word; 

			fstream fin("plaintext_dictionary_2.txt", fstream::in);
			while (fin >> word) {
				plaintextDictionary[word] = 1;
			}
		}

		bool validateDecrytedText(string ptext){
			string firstWord = "";
			for(int i = 0; i < ptext.size(); ++i){
				if(ptext[i] == ' '){
					break;
				}
				firstWord+=ptext[i];
			}


			return (plaintextDictionary.count(firstWord));
			//cout << firstWord << endl;

			/*
			string word; 
			bool valid = false;
			fstream fin(file, fstream::in);
			while (fin >> word) {
				if(word == firstWord){
					valid = true; 
					break;
				}
			}

			return valid; 
			*/
		}


		void initializeShifts(){
			//basically a multimap
			shifts['a'] = 1;
			shifts['b'] = 2;
			shifts['c'] = 3;
			shifts['d'] = 4;
			shifts['e'] = 5;
			shifts['f'] = 6;
			shifts['g'] = 7;
			shifts['h'] = 8;
			shifts['i'] = 9;
			shifts['j'] = 10;
			shifts['k'] = 11;
			shifts['l'] = 12;
			shifts['m'] = 13;
			shifts['n'] = 14;
			shifts['o'] = 15;
			shifts['p'] = 16;
			shifts['q'] = 17;
			shifts['r'] = 18;
			shifts['s'] = 19;
			shifts['t'] = 20;
			shifts['u'] = 21;
			shifts['v'] = 22;
			shifts['w'] = 23;
			shifts['x'] = 24;
			shifts['y'] = 25;
			shifts['z'] = 26;
			shifts[' '] = 27;

			shiftsToChars[1] = 'a';
			shiftsToChars[2] = 'b';
			shiftsToChars[3] = 'c';
			shiftsToChars[4] = 'd';
			shiftsToChars[5] = 'e';
			shiftsToChars[6] = 'f';
			shiftsToChars[7] = 'g';
			shiftsToChars[8] = 'h';
			shiftsToChars[9] = 'i';
			shiftsToChars[10] = 'j';
			shiftsToChars[11] = 'k';
			shiftsToChars[12] = 'l';
			shiftsToChars[13] = 'm';
			shiftsToChars[14] = 'n';
			shiftsToChars[15] = 'o';
			shiftsToChars[16] = 'p';
			shiftsToChars[17] = 'q';
			shiftsToChars[18] = 'r';
			shiftsToChars[19] = 's';
			shiftsToChars[20] = 't';
			shiftsToChars[21] = 'u';
			shiftsToChars[22] = 'v';
			shiftsToChars[23] = 'w';
			shiftsToChars[24] = 'x';
			shiftsToChars[25] = 'y';
			shiftsToChars[26] = 'z';
			shiftsToChars[27] = ' ';
		}

		vector<int> populate(){
			vector<int> result;
			result.push_back(19);
			result.push_back(5);
			result.push_back(9);
			result.push_back(15);
			result.push_back(18);
			result.push_back(0);

			return result;
		}


		map<int, int> findDistribution(string file){
			map<int, int> words;
			string word;
			int min = 1000000000;
			int minWordLength;


			fstream fin(file, fstream::in);
			while (fin >> word) {
				//cout << word  << endl;
				if(words.count(word.length()) && word != " "){
					words[word.length()] = words[word.length()] + 1;
				}
				else {
					words[word.length()] = 1;
				}
			}

			for (auto const& p : words){
		    	cout << p.first << ' ' << p.second << '\n';
		    	if (p.second < min){
		    		min = p.second;
		    		minWordLength = p.first;
		    	}

			}
			
			cout << "Lowest Frequency: " << minWordLength << " - " << min << endl;

			return words;
		}

		pair<char, int> findMaxChar(string file){
			map<char, int> chars;
			char ch;
			int max = 0;
			char maxChar;

			vector<int> maxFrequencies;
			pair<char, int> topChars[5];
			//pair<char, int> * t = &topChars;

			fstream fin(file, fstream::in);
			while (fin >> ch) {
				if(chars.count(ch)){
					chars[ch] = chars[ch] + 1;
				}
				else{
					chars[ch] = 1;
				}

				if(chars[ch] > max){
						max = chars[ch];
						maxChar = ch;
				}
			}

			for (auto const& p : chars){
				maxFrequencies.push_back(p.second);
			}

			sort(maxFrequencies.begin(), maxFrequencies.end());
			reverse(maxFrequencies.begin(), maxFrequencies.end());

			for (auto const& p : chars){
				if(p.second == maxFrequencies[0]){
					topChars[0].first = p.first;
					topChars[0].second = p.second;
				}
				if(p.second == maxFrequencies[1]){
					topChars[1].first = p.first;
					topChars[1].second = p.second;
				}
				if(p.second == maxFrequencies[2]){
					topChars[2].first = p.first;
					topChars[2].second = p.second;
				}
				if(p.second == maxFrequencies[3]){
					topChars[3].first = p.first;
					topChars[3].second = p.second;
				}
				if(p.second == maxFrequencies[4]){
					topChars[4].first = p.first;
					topChars[4].second = p.second;
				}


			}

			//cout << "Highest Frequency: " << topChars[0].first << " - " << topChars[0].second << endl;
			return(topChars[0]);
		}

		map<string, vector<string> > possibleMatches(string plain, string cipher){
			map<int, int> plainfreq = findDistribution(plain);
			//map<int, int> cipherfreq = findDistribution(cipher);
			int len;
			string word;
			vector<string> matches;
			map<string, vector<string> > result;

			for (auto const& p : plainfreq){
				if(p.second == 1){
					len = p.first;
					break;
				}
			}

			fstream cipherfin(cipher, fstream::in);
			while (cipherfin >> word) {
				if (word.length() == len){
					matches.push_back(word);
				}
			}

			fstream plainfin(plain, fstream::in);
			while (plainfin >> word) {
				if (word.length() == len){
					result[word] = matches; 
					break;
				}
			}

			return result;
			
		}

		map<int, int> shiftFrequency(map<string, vector<string> > matches){
			string plaintext = matches.begin()->first;
			vector<string> cipherMatches = matches.begin()->second;

			map<int, int> shiftFrequency;

			for (int outer = 0; outer<cipherMatches.size(); ++outer){
				for (int inner = 0; inner<cipherMatches[outer].length(); ++inner){
					int shift;

					//give shift value from absolute difference of cipher and plaintext
					shift = abs(cipherMatches[outer][inner]-plaintext[inner]);

					if (shiftFrequency.count(shift)){
						shiftFrequency[shift] = shiftFrequency[shift] + 1;
					}
					else{
						shiftFrequency[shift] = 1;
					}
				}
			}

			return shiftFrequency;
		}
		/*

		void findKeyLength(string file){
			string first24 = "";
			int it = 0;
			char ch;
			fstream fin(file, fstream::in);
			while (fin >> noskipws >> ch && it < 24){
				first24 += ch;
				it += 1;
			}
			
			cout << first24 << endl;
			vector< queue<char> > queues;
			for(int i = 0; i <= 24; ++i){
				queue<char> newQueue; 
				for(int j = 0; j < first24.length(); ++j){
					newQueue.push(first24[j]);
				}
				for(int k=0; k < i; ++k){
					newQueue.push('&');
					newQueue.pop();
				}
				queues.push_back(newQueue);
			}

			for(int z=0; z<queues.size(); ++z){
				queue<char> copy = queues[z];

				while (!copy.empty()){
		    		cout << copy.front() << " ";
		    		copy.pop();
		  		}
		  		cout << endl;
			}

		}
		*/




		//where the magic happens
		vector <vector<int> > keyBreak(string ctext, int keySize){
			//break my ciphertext into segments
			vector<string> segments;
			vector<string> symbols;
			vector< vector<char> > highFreqSymbols;
			string segment = "";

			vector< vector <int> > keyCandidates;
			//based on highest frequency characters within dicitonary 
			//{19, 5, 9, 15, 18, 0}
			vector<int> candidateShifts = populate();

			//vector<int> testKey = {26, 2, 10};

			char ch;
			//fstream fin(file, fstream::in);
			//while (fin >> noskipws >> ch)

			for(int segmentIter = 0; segmentIter < ctext.size(); ++segmentIter){
				ch = ctext[segmentIter];
				segment += ch;
				if(segment.length() >= keySize){
					segments.push_back(segment);
					segment = "";
				}
			}
			if(segment.length() > 0){
				segments.push_back(segment);
				segment = "";
			}

			/*cout << "Segments: " << segments.size() << endl;
			for(int i = 0; i<segments.size(); ++i){
				cout << segments[i] << endl;
			}*/
			
			//cout << endl;

			//separate segments by k[i]
			for(int x = 0; x < keySize; ++x){
				string symbol = "";
				for(int y = 0; y < segments.size(); ++y){
					if(x < segments[y].length()){
						symbol += segments[y][x];
					}
				}
				symbols.push_back(symbol);
			}

			for(int j = 0; j<symbols.size(); ++j){
				//cout << symbols[j] << endl;
			}

			//find char of highest frequency
			for(int p = 0; p<symbols.size(); ++p){
				int max = 0;
				vector<char> maxChars;
				map<char, int> chars;

				for(int t = 0; t<symbols[p].length(); ++t){
					if(chars.count(symbols[p][t])){
						chars[symbols[p][t]] = chars[symbols[p][t]] + 1;
					}
					else{
					chars[symbols[p][t]] = 1;
					}

					if(chars[symbols[p][t]] == max){
						maxChars.push_back(symbols[p][t]);
					}

					if(chars[symbols[p][t]] > max){
						max = chars[symbols[p][t]];
						maxChars.clear();
						maxChars.push_back(symbols[p][t]);
					}
				}

				highFreqSymbols.push_back(maxChars);
			}

			//cout << "Candidates: " << highFreqSymbols.size() << endl;
			for(int z = 0; z< highFreqSymbols.size(); ++z){
				for(int c = 0; c<highFreqSymbols[z].size(); ++c){
					cout << highFreqSymbols[z][c];
				}
				cout << ", ";
			}
			cout << endl;

			//shift back by highest frequency character from the plainttext dictionary
			vector<int> key;
			initializeShifts();

			char shift = findMaxChar("plaintext_dictionary_2.txt").first;
			for(int k = 0; k < highFreqSymbols.size(); k++){
				int keyBit = (((shifts[highFreqSymbols[k][0]] - shifts[shift]) % 27) + 27) % 27;

				/////////////////////////////
				vector <int> bitCandidates;
				for(int c = 0; c < candidateShifts.size(); ++c){
					int keyCandidate;
					if((shifts[highFreqSymbols[k][0]] - candidateShifts[c]) >= 0){
						keyCandidate = (shifts[highFreqSymbols[k][0]] - candidateShifts[c]);
					}
					else{
						keyCandidate = ((shifts[highFreqSymbols[k][0]] - candidateShifts[c]) + 27) % 28;
					}			
					//int keyCandidate =  ((shifts[highFreqSymbols[k][0]] - candidateShifts[c]) + 27) % 28;
					bitCandidates.push_back(keyCandidate); 
				}

				keyCandidates.push_back(bitCandidates);
				//cout << keyBit << endl;
				key.push_back(keyBit);
			}

			
			cout << "Key: ";
			for(int y = 0;y<key.size(); ++y){
				cout << key[y] << " ";
			}
			cout << endl;
			defaultKey = key;
			

			for(int ee = 0; ee < keyCandidates.size(); ++ee){
				for(int pp = 0; pp < keyCandidates[ee].size(); ++pp){
					cout << keyCandidates[ee][pp] << " ";
				}
				cout << endl;
			}

			//returns 6^T permutations all of size T
			vector< vector<int> > keyPermutations;
			vector<int> row;
			combinations(keyCandidates, 0, row);
			keyPermutations = comb;

			/*
			cout << keyPermutations.size() << endl;
			bool keyFound;
			for(int ii = 0; ii<keyPermutations.size(); ++ii){
				vector<int> attemptkey;
				keyFound = true;
				for(int jj = 0; jj<keyPermutations[ii].size(); ++jj){
					attemptkey.push_back(keyPermutations[ii][jj]);
					if(testKey[jj] != keyPermutations[ii][jj]){
						keyFound = false; 
						break;
					}
				}
				if(keyFound){
					cout << "Index - " << ii << endl;
					for(int oo = 0; oo < attemptkey.size(); ++oo){
						cout << attemptkey[oo] << " ";
					}
					cout << endl;
					break;
				}
			}

			if(keyFound){
				cout << "KEY FOUND!!!" << endl;
			}
			else{
				cout << "Failed to find key" << endl;
			}*/

			return(keyPermutations);

		}




		string decryptTest(string file, vector<int> key, int keySize){
			string text = "";
			int keyIterator = 0;
			char ch;
			fstream fin(file, fstream::in);
			while (fin >> noskipws >> ch) {
				//cout << ch;
				char messageBit;
				if(shifts[ch]-key[keyIterator] > 0){
					//cout << shiftsToChars[(shifts[ch]-key[keyIterator])] << endl;
					messageBit = shiftsToChars[(shifts[ch]-key[keyIterator])];
				}
				else{
					//cout << shiftsToChars[((shifts[ch]-key[keyIterator])+27)%28];
					messageBit = shiftsToChars[((shifts[ch]-key[keyIterator])+27)%28];
				}
				
				cout << messageBit;
				text += messageBit;
				if(keyIterator >= keySize-1){
					keyIterator = 0;
				}
				else{
					keyIterator += 1;
				}
			}
			
			return(text);
		}





		string decrypt(string ctext, int keySize, string dictionary){
			initializeShifts();
			mapDictionary();


			//creates 2D vector of all possible keys (each possible key is its own vector)
			vector< vector<int> > possibleKeys = keyBreak(ctext, keySize);
			//vector<int> key = {26, 2, 10};

			
			string text = "";

			/*cout << "The correct key - ";
			for(int yy = 0; yy < possibleKeys[181].size(); ++yy){
				cout << possibleKeys[181][yy] << " ";
			}
			cout << endl;*/
			
			//starts timer that will timeout if finding the correct key takes too long
			//time_t timeStart;
			//timeStart = time(NULL);
			bool keyFound;
			for(int ii = 0; ii<possibleKeys.size(); ++ii){

				/*if(timeStart > 55){
					cout << "TIMEOUT" << endl;
					break;
				}*/

				string ptext = "";
				vector<int> attemptkey;
				keyFound = true;

				

				int keyIterator = 0;
				char ch;
				//fstream fin(file, fstream::in);
				//while (fin >> noskipws >> ch)
				for(int ctextIter = 0; ctextIter < ctext.size(); ++ctextIter){
					ch = ctext[ctextIter];
					char messageBit;
					if(shifts[ch]-possibleKeys[ii][keyIterator] > 0){
						/*
						if(ii == 181 && keyIterator == 0){
							cout << "My Key: " << possibleKeys[ii][0] << " " << possibleKeys[ii][1] << " " << possibleKeys[ii][2] << endl;
							cout << shiftsToChars[(shifts[ch]-possibleKeys[ii][keyIterator])] << endl;
						}*/
						messageBit = shiftsToChars[(shifts[ch]-possibleKeys[ii][keyIterator])];
					}
					else{
						/*
						if(ii == 181 && keyIterator == 0){
							cout << shiftsToChars[((shifts[ch]-possibleKeys[ii][keyIterator])+27)%28] << endl;
						}*/
						messageBit = shiftsToChars[((shifts[ch]-possibleKeys[ii][keyIterator])+27)%28];
					}
				
					ptext += messageBit;
					if(keyIterator >= keySize-1){
						keyIterator = 0;
					}
					else{
						keyIterator += 1;
					}	
				}

				if(validateDecrytedText(ptext) == false){
					keyFound = false; 
				}
				else{
					attemptkey = possibleKeys[ii];
				}

				
				if(keyFound){
					text = ptext;
					cout << "KEY FOUND" << endl;
					decryptionSuccess = true;
					for(int oo = 0; oo < attemptkey.size(); ++oo){
						cout << attemptkey[oo] << " ";
					}
					cout << endl;
					cout << text << endl << endl;
					//fin.close();
					break;
				}
				//fin.close();
			}

			if(!keyFound){
				cout << "KEY NOT FOUND" << endl << endl;
				//decryptTest(file, defaultKey, keySize);
			}
			/*
			char ch;
			fstream fin(file, fstream::in);
			while (fin >> noskipws >> ch) {
				char messageBit;
				if(shifts[ch]-key[keyIterator] > 0){
					messageBit = shiftsToChars[(shifts[ch]-key[keyIterator])];
				}
				else{
					messageBit = shiftsToChars[((shifts[ch]-key[keyIterator])+27)%28];
				}
				
				cout << messageBit;
				text += messageBit;
				if(keyIterator >= keySize-1){
					keyIterator = 0;
				}
				else{
					keyIterator += 1;
				}
			}*/
			
			
			return(text);
		}


		vector<string> decryptAllTs(string ctext, string dictionary){
			vector<string> allPlainTexts;
			string text;

			for(int i = 5; i < 7; ++i){
				cout << "Checking T Size: " << i << endl;
				string ptext = decrypt(ctext, i, dictionary);
				if(decryptionSuccess){
					cout << "Success" << endl;
					text = ptext;
					decryptionSuccess = false;
					break;
				}
				//allPlainTexts.push_back(ptext);
			}

			return(allPlainTexts);
		}

		//creates files to hold all individual cipher texts. Not too pretty but good in terms of modularity 
		vector<string> createCipherFiles(string file){
			vector<string> cipherFiles;
			int inc = 1;
			string line;

			fstream fin(file, fstream::in);
			while(getline(fin, line)){
				string fileName = "cipherText_" + to_string(inc) + ".txt";

				fstream infile;
				infile.open(fileName, fstream::out);
				infile << line;
				infile.close();

				cipherFiles.push_back(fileName);
				inc += 1;
			}

			return cipherFiles;
		}

		vector<string> createCipherVariables(string file){
			vector<string> cipherVariables;
			string line;

			fstream fin(file, fstream::in);
			while(getline(fin, line)){
				cipherVariables.push_back(line);
			}

			return cipherVariables;

		}

		void decryptFile(string file, string dictionary){

			//every line is it's own cipher text
			//vector<string> lines = createCipherFiles(file);
			vector<string> ctexts = createCipherVariables(file);

			for(int iterator = 0; iterator < ctexts.size(); ++iterator){
				cout << "Line " + to_string(iterator + 1) + " - " << endl; 
				decryptAllTs(ctexts[iterator], dictionary);
				cout << endl;
			}

			/*for(int iterator = 0; iterator < lines.size(); ++iterator){
				cout << "Line " + to_string(iterator + 1) + " - " << endl; 
				decryptAllTs(lines[iterator], dictionary);
				cout << endl;
			}
			for(int removeIterator = 0; removeIterator < lines.size(); ++removeIterator){
				string fileName = lines[removeIterator];
				char char_array[fileName.length() + 1]; 
				strcpy(char_array, fileName.c_str());
				std::remove(char_array);
			}*/
		}



};