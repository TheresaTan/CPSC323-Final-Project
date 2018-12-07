//
// Created by Theresa Tanubrata on 12/7/18.
//

#ifndef VECTOR_STRING_INCLUDE
#define VECTOR_STRING_INCLUDE

#include <iostream>
#include <fstream>		//file reading
#include <string>
#include <vector>
#include <sstream>

#include <stdlib.h>

//#define PAUSE cout << "\n\n"; system("pause");

using namespace std;

void readfile(string &); // read a file
void remove_white_space(string &); // remove whitespace at the beginning of strings
void remove_single_comments(string &); // remove single line comments
void remove_multiple_comments(fstream&, string&); // remove multiple line comments
void proper_spacing(string&); // add proper spacing to the line

void program_vector(vector<string>&); // populate a vector with the tokens found in a program file


// & in parameter to pass by reference and manipulate string::file_contents data
void readfile(string &file_contents) { // a function to read a file into a string
    fstream ifile;

    ifile.open("/Users/Theresa/CLionProjects/untitled13/finalp1.txt");

    if (!ifile.is_open()) {
        std::cout << "finalp1.txt NOT FOUND...\n\n";
        //PAUSE
    }
    //else cout << "finalp1.txt FOUND!\n\n";

    string str_line;

    while (!ifile.eof()) {
        getline(ifile, str_line);

        remove_white_space(str_line);				// remove white space

        remove_multiple_comments(ifile, str_line);	// REMOVE MULTIPLE LINE COMMENTS

        remove_single_comments(str_line);			// remove single line comments

        proper_spacing(str_line);					// ADD PROPER SPACING

        if (str_line.length() > 0 &&									// if length is greater than 0
            str_line.find_first_not_of(' ') != std::string::npos &&		// if the line doesnt consist of space
            str_line.find_first_not_of('\t') != std::string::npos) {	// if the line doesnt consist of tabs

            while (str_line.back() == ' ') {
                str_line.pop_back();
            }

            if (!str_line.find("end")) {
                file_contents += str_line;
            } else file_contents += str_line + "\n";

        }
    }


    //cout << "\tSTRING CONTENTS FOR FILE AFTER\n\t\t-WHITE SPACE REMOVAL\n\t\t-SINGLE LINE COMMENT REMOVAL\n\t\t-MULTILINE COMMENT REMOVAL\n\n" << file_contents; // string::file_contents population test
    ifile.close();

    ofstream ofile;

    ofile.open("finalp2.txt");
    ofile << file_contents;
    ofile.close();

} // end void readfile(string &)

void remove_white_space(string &str_line) {
    //		REMOVING LEADING WHITE SPACE

    // this function checks to see if the line is all white_space, checking for space and tab
    // by default, std::string.find_first_not_of(<char>) will return std::string::npos (the maximum amount of characters in a string)
    // if std::string::npos (the maximum amount of characters in a string) is not returned, then there was a character other than space ' ' or tab '\t'
    if (str_line.find_first_not_of(' ') != std::string::npos &&
        str_line.find_first_not_of('\t') != std::string::npos) {

        //cout << "BEFORE " << str_line.length() << " : " << str_line << endl; // DEBUG

        for (int element = 0; str_line[element];) {

            if (isspace(str_line[element])) {
                while (isspace(str_line[element])) {
                    //cout << "\tSPACE FOUND\n"; // DEBUG
                    element++;
                }
                continue;
            }

            if (!isspace(str_line[element])) {
                if (element != 0) {
                    //cout << "\tERASING " << element << "ELEMENTS!" << endl; // DEBUG
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
                //cout << "DELETING EXTRA WS\n"; // DEBUG
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

        // cout << "<// FOUND AT> : " << found_at << "\n"; // std::string.find() functionality test // DEBUG

        //the following occurs while the length of the string is not equal to the 0th position that the "//" string was found
        //it will remove the comment
        while (str_line.length() != found_at) {
            str_line.pop_back(); // pop until there are no more white spaces
        }
    }
}

void remove_multiple_comments(fstream &ifile, string &str_line) {

    bool multi = 0;

    size_t start_found_at = 0;
    size_t end_found_at = 0;

    //	REMOVE MULTIPLE LINE COMMENTS

    start_found_at = str_line.find("/*"); // by default, the std::string.find(<string>) will return std::string::npos (the maximum amount of characters in a string)
    if (start_found_at != std::string::npos) {

        //cout << "Start Multi Comment Found\n"; // DEBUG
        //cout << str_line << endl; // DEBUG

        multi = 1; // start multiple line comment symbol found

        end_found_at = str_line.find("*/");	// see if "*/" is in this line
        if (end_found_at != std::string::npos) {
            str_line.erase(str_line.begin() + start_found_at, str_line.begin() + end_found_at + 1); // Erase everything from the beginning of the line up to and including the / in */

            multi = 0; // multiple line comment end symbol found. multiple line comment resolved
        }

        else { // if "*/" is not in the line

            while (multi) { // while multiple line comment end symbol not resolved

                getline(ifile, str_line); // grab the next line
                //cout << str_line << endl; // DEBUG
                end_found_at = str_line.find("*/");

                if (end_found_at != std::string::npos) {
                    //cout << "End Multi Comment Found\n"; // DEBUG
                    str_line.erase(str_line.begin(), str_line.begin() + end_found_at + 2);
                    multi = 0;
                }
            }
        }
    }	//	END REMOVE MULTIPLE LINE COMMENTS
}

void proper_spacing(string &str_line) {
    //		ADD PROPER SPACING

    for (int element = 0; element < str_line.length(); element++) { // walk the string

        // symbol exception ex +2
        // break if the next character is a number
        if (element != 0 &&
            (str_line[element] == '+' ||
             str_line[element] == '-') &&
            isdigit(str_line[element + 1])) {

            break;
        }

        // if there is a punctuation before another token without spaces in between (example: ",TOKEN")
        // add a space where the token begins; between the punctuation and the next token (", TOKEN")
        if (element != 0 &&						// not the beginning
            isalnum(str_line[element]) &&		// current is number or letter
            ispunct(str_line[element - 1])) {	// previous is a punctuation

            str_line.insert(str_line.begin() + element, ' ');
            //element += 1; // increment by 1 because the string increases by one and following chars from this position have their address incremented by one
        }

        // if there is a punctuation and it is not the first element of the string
        // add a space before it if there doesnt already exist a space character
        if (element != 0 &&						// not the beginning
            ispunct(str_line[element]) &&		// current is puncuation
            str_line[element - 1] != ' ') {		// previous is not a space

            str_line.insert(str_line.begin() + element, ' ');
            //element += 1; // increment by 1 because the string increases by one and following chars from this position have their address incremented by one
        }

    }
}

void program_vector(vector<string>& vector_given_tokens) {

    // CREATING TOKENS FROM THE FILE AND PLACING THEM IN A VECTOR

    fstream ifile2;
    ifile2.open("finalp2.txt");

    if (!ifile2.is_open()) {
        cout << "finalp2.txt not found...\n";
        //PAUSE
          //      exit;
    }

    //cout << "\nfinalp2.txt FOUND!\n";
    string str_line;
    string word;

    while (!ifile2.eof()) {
        getline(ifile2, str_line);
        for (int x = 0; x < str_line.length(); x++) {
            if (str_line[x] == ' ' || x + 1 == str_line.length()) {

                if (x + 1 == str_line.length()) {
                    word += str_line[x];
                }

                while (word.back() == ' ') {
                    word.pop_back();
                }

                vector_given_tokens.push_back(word);
                word.clear();

                continue;
            }

            word += str_line[x];
        }
    }

    //	VECTOR POPULATION CHECK

    /*for (int x = 0; x < vector_words.size(); x++) {
        cout << x << ":\t" << vector_words[x] << "\n";
    }*/
}
#endif

