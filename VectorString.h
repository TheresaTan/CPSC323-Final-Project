#ifndef VECTOR_STRING_INCLUDE
#define VECTOR_STRING_INCLUDE

#include <iostream>
#include <fstream>		//file reading
#include <string>
#include <vector>

#define PAUSE cout << "\n\n"; system("pause");

using namespace std;

void program_vector(vector<string>& vector_given_tokens) {

	// CREATING TOKENS FROM THE FILE AND PLACING THEM IN A VECTOR

	fstream ifile2;
	ifile2.open("finalp2.txt");

	if (!ifile2.is_open()) {
		cout << "finalp2.txt not found...\n";
		PAUSE
			return;
	}

	cout << "\nfinalp2.txt FOUND!\n";
	string str_line;
	string word;

	while (!ifile2.eof()) {
		getline(ifile2, str_line);
		for (int x = 0; x < str_line.length(); x++) {
			if (str_line[x] == ' ' || x + 1 == str_line.length()) {

				if (x + 1 == str_line.length()) {
					word += str_line[x];
				}

				//word += '\0';
				vector_given_tokens.push_back(word);
				word.clear();

				continue;
			}

			word += str_line[x];
		}
	}

	ifile2.close();
}

#endif
