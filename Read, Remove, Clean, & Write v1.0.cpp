// FirstName	LastName	CWID			Student Email
// Dominick		Weaver		891791733		unrealsuperhero@csu.fullerton.edu

#include <iostream>
#include <fstream>		//file reading
#include <string>
#include <vector>

#define PAUSE cout << "\n\n"; system("pause");

using namespace std;

void readfile(string &); // read a file
void remove_white_space(string &); // remove ws at the beginning of strings
void remove_single_comments(string &); // remove single line comments


int main() {

	string file_contents;

	readfile(file_contents);

	//remove_multi_comments(file_contents); //remove multi line comments

	//remove_comments(file_contents);

	//ideas:
	//	use parsing tokens to break up non white space substrings and then space them out ex token_n + ' ' + token_n+1

	PAUSE
		return 0;
}

// & in parameter to pass by reference and manipulate string::file_contents data
void readfile(string &file_contents) { // a function to read a file into a string
	fstream ifile;

	ifile.open("finalp1.txt");

	if (!ifile.is_open()) {
		std::cout << "finalp1.txt NOT FOUND...\n\n";
		PAUSE
			exit;
	}
	else
		cout << "finalp1.txt FOUND!\n\n";

	string str_line;
	bool multi = 0;

	size_t start_found_at = 0;
	size_t end_found_at = 0;

	while (!ifile.eof()) {
		getline(ifile, str_line);

		remove_white_space(str_line); //remove white space

		//	REMOVE MULTIPLE LINE COMMENTS

		start_found_at = str_line.find("/*"); // by default, the std::string.find(<string>) will return std::string::npos (the maximum amount of characters in a string)
		if (start_found_at != std::string::npos) {
			//cout << "Start Multi Comment Found\n";
			multi = 1;

			end_found_at = str_line.find("*/");	// see if "*/" is in this line
			if (end_found_at != std::string::npos) {
				str_line.erase(str_line.begin() + start_found_at, str_line.begin() + end_found_at + 1);

				str_line += str_line;

				multi = 0;
			}

			else {
				str_line.pop_back();
				getline(ifile, str_line); // grab the next line

				while (multi) {
					end_found_at = str_line.find("*/");
					if (end_found_at != std::string::npos) {
						//cout << "End Multi Comment Found
						str_line.erase(str_line.begin(), str_line.begin() + end_found_at + 2);
						multi = 0;
					}
				}
			}
		}

		remove_single_comments(str_line); //remove single line comments



	//		ADD PROPER SPACING

		for (int element = 0; element < str_line.length(); element++) { // walk the string
			if (ispunct(str_line[element])) {
				//std::cout << str_line[element] << " ";

				if (element != 0 && str_line[element - 1] != ' ') {
					str_line.insert(str_line.begin() + element, ' ');
					element += 1;
				}
			}
		}

		file_contents += str_line;

		if (str_line.length() > 0 &&
			str_line.find_first_not_of(' ') != std::string::npos &&
			str_line.find_first_not_of('\t') != std::string::npos)

			file_contents += "\n";
	}


	cout << "\tSTRING CONTENTS FOR FILE AFTER\n\t\t-WHITE SPACE REMOVAL\n\t\t-SINGLE LINE COMMENT REMOVAL\n\t\t-MULTILINE COMMENT REMOVAL\n\n" << file_contents; // string::file_contents population test
	ifile.close();

	ofstream ofile;

	ofile.open("finalp2.txt");
	ofile << file_contents;
	ofile.close();

} // end void readfile(string &)

void remove_white_space(string &str_line) {
	//		REMOVING WHITE SPACE

	// this function checks to see if the line is all white_space, checking for space and tab
	// by default, std::string.find_first_not_of(<char>) will return std::string::npos (the maximum amount of characters in a string)
	// if std::string::npos (the maximum amount of characters in a string) is not returned, then there was a character other than space ' ' or tab '\t'
	if (str_line.find_first_not_of(' ') != std::string::npos &&
		str_line.find_first_not_of('\t') != std::string::npos) {

		//cout << "BEFORE " << str_line.length() << " : " << str_line << endl;

		for (int element = 0; str_line[element];) {

			if (isspace(str_line[element])) {
				while (isspace(str_line[element])) {
					//cout << "\tSPACE FOUND\n";
					element++;
				}
				continue;
			}

			//if (str_line[element] == '\t') {
			//	while (str_line[element] == '\t') {
			//		//cout << "\tTAB FOUND\n";
			//		element++;
			//	}
			//	continue;
			//}

			if (!isspace(str_line[element])) {
				if (element != 0) {
					//cout << "\tERASING " << element << "ELEMENTS!" << endl;
					str_line.erase(str_line.begin(), str_line.begin() + element); // erase from beginning to a position
				}
				break;
			}

		}

		//cout << "AFTER  " << str_line.length() << " : " << str_line << "\n\n";
	} // end leading white space if statement check


	//		DELETE EXTRA WHITE SPACES IN LINES

	for (int element = 0; element < str_line.length(); element++) { // walk the string
		if (isspace(str_line[element])) {
			while (isspace(str_line[element + 1])) {
				str_line.erase(str_line.begin() + element);
				//cout << "DELETING EXTRA WS\n";
			}
		}
	}

}

void remove_single_comments(string &str_line) {
	//		REMOVING SINGLE LINE ("//") COMMENTS

	size_t found_at = 0;
	int elements = str_line.length(); // length of the string

	found_at = str_line.find("//"); // by default, the std::string.find(<string>) will return std::string::npos (the maximum amount of characters in a string)

	if (found_at != std::string::npos) {

		// cout << "<// FOUND AT> : " << found_at << "\n"; // std::string.find() functionality test

		//the following occurs while the length of the string is not equal to the 0th position that the "//" string was found
		//it will remove the comment
		while (str_line.length() != found_at) {
			str_line.pop_back();
		}
	}
}
