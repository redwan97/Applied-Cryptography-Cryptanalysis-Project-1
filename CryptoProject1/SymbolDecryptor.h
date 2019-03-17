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

		void allPermutations(vector<int> shifts, string word){
			
		}
};