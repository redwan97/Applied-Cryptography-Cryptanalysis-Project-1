#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

class SymbolDecryptor {
	private:
		map<char, int> shifts;
		map<int, char> shiftsToChars;

	public:
		

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

	cout << "Highest Frequency: " << topChars[0].first << " - " << topChars[0].second << endl;
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

void findBestGuess(string file, map<int, int> shiftFrequency){
	vector<int> shifts;

	for (auto const& p : shiftFrequency){
		shifts.push_back(p.first);
	} 

	//Go word by word giving best decrypted guess
	string word;
	fstream fin(file, fstream::in);
	while (fin >> word) {

	}

}


vector< vector<int> > allKeys(vector<int> Candidates, vector<int> highFreqs){
	vector< vector<int> > allKeys;


}


vector<int> keyBreak(string file, int keySize){
	//break my ciphertext into segments
	vector<string> segments;
	vector<string> symbols;
	vector< vector<char> > highFreqSymbols;
	string segment = "";


	char ch;
	fstream fin(file, fstream::in);
	while (fin >> noskipws >> ch){
		segment += ch;
		if(segment.length() >= keySize){
			segments.push_back(segment);
			segment = "";
		}
	}

	
	for(int i = 0; i<segments.size(); ++i){
		cout << segments[i] << endl;
	}
	
	cout << endl;

	//separate segments by k[i]
	for(int x = 0; x < keySize; ++x){
		string symbol = "";
		for(int y = 0; y < segments.size()-1; ++y){
			symbol += segments[y][x];
		}
		symbols.push_back(symbol);
	}

	for(int j = 0; j<symbols.size(); ++j){
		cout << symbols[j] << endl;
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

	cout << "Candidates: " << highFreqSymbols.size() << endl;
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

		//cout << keyBit << endl;
		key.push_back(keyBit);
	}

	cout << "Key: ";
	for(int y = 0;y<key.size(); ++y){
		cout << key[y] << " ";
	}
	cout << endl;

	return(key);

}

void decrypt(string file, int keySize){
	vector<int> key = keyBreak(file, keySize);

	int keyIterator = 0;

	cout << "testing" << endl;

	
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
		if(keyIterator >= keySize-1){
			keyIterator = 0;
		}
		else{
			keyIterator += 1;
		}
	}
	

}

	vector<int> cipherKeyBreak(string ctext, int keySize, string dictionary){
		//break my ciphertext into segments
		vector<string> segments;
		vector<string> symbols;
		vector< vector<char> > highFreqSymbols;
		string segment = "";


		/*
		char ch;
		fstream fin(file, fstream::in);
		while (fin >> noskipws >> ch){
			segment += ch;
			if(segment.length() >= keySize){
				segments.push_back(segment);
				segment = "";
			}
		}*/

		for(int iter = 0; iter < ctext.length(); ++iter){
			segment += ctext[iter];
			if(segment.length() >= keySize){
				segments.push_back(segment);
				segment = "";
			}		
		}
		cout << "testing" << endl;
		cout << ctext << endl;
		cout << segments.size() << endl;
		for(int i = 0; i<segments.size(); ++i){
			cout << segments[i] << endl;
		}
		
		cout << endl;

		//separate segments by k[i]
		for(int x = 0; x < keySize; ++x){
			string symbol = "";
			for(int y = 0; y < segments.size()-1; ++y){
				symbol += segments[y][x];
			}
			symbols.push_back(symbol);
		}

		for(int j = 0; j<symbols.size(); ++j){
			cout << symbols[j] << endl;
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

		cout << "Candidates: " << highFreqSymbols.size() << endl;
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

		char shift = findMaxChar(dictionary).first;
		for(int k = 0; k < highFreqSymbols.size(); k++){
			int keyBit = (((shifts[highFreqSymbols[k][0]] - shifts[shift]) % 27) + 27) % 27;

			//cout << keyBit << endl;
			key.push_back(keyBit);
		}

		cout << "Key: ";
		for(int y = 0;y<key.size(); ++y){
			cout << key[y] << " ";
		}
		cout << endl;

		return(key);

	}

	void cipherDecrypt(string ctext, int keySize, string dictionary){
		vector<int> key = cipherKeyBreak(ctext, keySize, dictionary);

		int keyIterator = 0;

		
		for(int i = 0; i < ctext.length(); ++i){
			char messageBit;
			char ch = ctext[i];
			if(shifts[ch]-key[keyIterator] > 0){
				messageBit = shiftsToChars[(shifts[ch]-key[keyIterator])];
			}
			else{
				messageBit = shiftsToChars[((shifts[ch]-key[keyIterator])+27)%28];
			}
			
			cout << messageBit;
			if(keyIterator >= keySize-1){
				keyIterator = 0;
			}
			else{
				keyIterator += 1;
			}		
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
			if(keyIterator >= keySize-1){
				keyIterator = 0;
			}
			else{
				keyIterator += 1;
			}
		}*/
		

	}

};