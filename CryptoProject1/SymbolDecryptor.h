#include <iostream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

class SymbolDecryptor {
	public:
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

		map<char, int> findMaxChar(string file){
			map<char, int> chars;
			char ch;
			int max = 0;
			char maxChar;

			vector<int> maxFrequencies;
			pair<char, int> topChars[5];

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

			//cout << "F: " << maxFrequencies[0] << endl; 
			cout << "Highest Frequency: " << topChars[0].first << " - " << topChars[0].second << endl;
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





		void cipherBreak(string file, int keySize){
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

		}
};