#pragma once

#ifndef ENCRYPT_H_
#define ENCRYPT_H_

int siFinder(std::string str, char c);																		//Encryption helper function
std::string encrypt(std::string s);																			//Encryption function
std::string encrypt2(std::string s);																		//Encryption function


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

#endif ENCRYPT_H_