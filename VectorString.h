//
// Header file that contains functions for all three parts
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
//PART I FUNCTIONS
void readfile(string &); // read a file
void remove_white_space(string &); // remove whitespace at the beginning of strings
void remove_single_comments(string &); // remove single line comments
void remove_multiple_comments(fstream&, string&); // remove multiple line comments
void proper_spacing(string&); // add proper spacing to the line
void program_vector(vector<string>&); // populate a vector with the tokens found in a program file
void walk_stack(vector<string>&); //used to debug vectors


//PART II FUNCTIONS
bool check_file_for_errors(vector<string>&); //Check file for any automatic errors
bool check_spelling(string&); //Check spelling for integer and word



//PART III FUNCTION
void create_cpp_file(vector<string>&); //Translate finalp2.txt file into c++ program



// & in parameter to pass by reference and manipulate string::file_contents data
void readfile(string &file_contents) { // a function to read a file into a string
    fstream ifile;

    ifile.open("finalp1.txt");

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




void walk_stack(vector<string>& state_stack){
    vector<string> temp = state_stack;
    cout << "Current Stack: ";
    for(auto it = temp.begin(); it < temp.end(); it++){
        cout << *it << " \t";
    }
    cout << endl;
}



bool check_file_for_errors(vector<string>& vector_given_tokens){
    //counters for the parentheses
    int p_open = 0, p_close = 0;
    //temporary vector string to keep track of declared variables
    vector<string> temp;

    //checks if program is in the file
    if(vector_given_tokens[0] != "program"){
        cout << endl;
        cout << "program \tis expected\n";
        return true;
    }

    //checks if end is in the file
    if(vector_given_tokens[vector_given_tokens.size()-1] != "end"){
        cout << endl;
        cout << "end \tis expected\n";
        return true;
    }

    //loops through the file to find any undefined variables, or illegal expressions
    for(int i = 0; i < vector_given_tokens.size(); i++){
        if(vector_given_tokens[i] == "("){

            //counts left parentheses
            p_open++;
        }else if(vector_given_tokens[i] == ")"){

            //counts right parentheses
            p_close++;
        }

        if(vector_given_tokens[i] == "var"){

            //looks for variables and pushes them on a temporary vector
            //int j = i+1;
            //increments to the beginning of the declaration list
            i++;
            bool dec_list_done = false;

            //keeps looping through the declaration list until it reaches the end (: or integer)
            while(!dec_list_done){

                //if reading : or integer then the declaration list of variables is done
                //put : and integer and ; in case one of them is missing from the file
                if(vector_given_tokens[i] == ":" || vector_given_tokens[i] == "integer" || vector_given_tokens[i] == ";"){
                    dec_list_done = true;
                }

                //pushes back only the variables and no punctuation marks
                if(vector_given_tokens[i] != "," && vector_given_tokens[i] != ":") {
                    temp.push_back(vector_given_tokens[i]);
                }
                i++;
            }
        }


        //looping thorugh part that uses the declared variables: assigning values, showing values, and changing values
        //Mainly looks for any illegal expressions or undefined variables being used
        if(vector_given_tokens[i] == "begin" && !temp.empty()){
            int k = i+1;
            //current variable being looked at
            string var_name;
            //string used to check if the expression is legal
            string check_expression;


            while(vector_given_tokens[k] != "end"){
                var_name = vector_given_tokens[k];
                auto it = var_name.begin();
                if( (*it >='a' && *it <= 'e')|| (*it >= '0' && *it <= '9') ){
                    //specifically checks the variables
                    if(*it >='a' && *it <= 'e'){
                        bool defined = false;
                        for(int l = 0; l < temp.size(); l++){
                            if(temp[l] == var_name){
                                defined = true;
                            }
                        }
                        if(!defined){
                            cout << endl;
                            cout << var_name << "\tUndefined Expression!\n";
                            return true;
                        }
                    }

                    //checks whether expression is valid
                    //this iterates to the next token
                    check_expression = vector_given_tokens[k+1];
                    auto it2 = check_expression.begin();
                    //checks if the next token after a variable or a number is a variable, number or '('
                    if( (*it2 >= 'a' && *it2 <= 'e') || *it2 == '(' || (*it2 >= '0' && *it2 <= '9')){
                        cout << endl;
                        cout << "Illegal Expression\n";
                        return true;
                    }


                }else if(*it == '+' || *it == '*' || *it == '('){
                    check_expression = vector_given_tokens[k+1];
                    auto it3 = check_expression.begin();

                    if(*it3 == '+' || *it3 == '*' || *it3 == ')'){
                        cout << endl;
                        cout << "Illegal Expression\n";
                        return true;
                    }
                }
                k++;

            }
        }


    }

    //checking if the left parentheses or right parentheses is more than the other
    if(p_open < p_close){
        cout << endl;
        cout << "(\t Left Parentheses is missing.\n";
        return true;
    }else if(p_open > p_close){
        cout << endl;
        cout << ")\t Right Parentheses is missing.\n";
        return true;
    }

    //returns false if there are no automatic errors in the file
    return false;
}

//Only checks the spelling of the words integer and show
bool check_spelling(string& word){
    //checks to see if any of the letters in the referenced word contains any of the letters from the words "integer" or "show"
    for(auto it = word.begin(); it != word.end(); ++it){
        if(*it == 'i' || *it == 'n' || *it == 't' || *it == 'e' || *it == 'g' || *it == 'r'){
            cout << endl;
            cout << "Integer is misspelled!\n";
            return true;
        }else if(*it == 's' || *it == 'h' || *it == 'o' || *it == 'w'){
            cout << endl;
            cout << "Show is misspelled!\n";
            return true;
        }
    }
    return false;
}


//PART III FUNCTION

//CREATING THE FILEP3.CPP
void create_cpp_file(vector<string>& vector_given_tokens){
    // Create .cpp file for output
    fstream ifile3;
    ifile3.open("filep3.cpp", ios::out);

    // bool flag for tabs within "int main()"
    bool tabFlag = false;

    cout << "\nCreating new filep3.cpp\n\n";

    // Begin iterating through vector
    for (int y = 0; y < vector_given_tokens.size(); y++) {

        // Rule for keyword "program"
        if (vector_given_tokens[y] == "program") {
            ifile3 << "#include <iostream>" << "\n"
                   << "using namespace std;" << "\n";

            while (vector_given_tokens[y] != ";")	// Increment vector position while ';' is not found
                y++;
        }


            // Rule for keyword "var"
        else if (vector_given_tokens[y] == "var") {
            y += 1;	// Skip "var" token

            do {
                if (vector_given_tokens[y] == "integer")		// Shorten "integer" into "int".
                    ifile3 << "int" << ' ';
                else
                    ifile3 << vector_given_tokens[y] << ' ';

                y += 1;	// Increment vector position

            } while (vector_given_tokens[y] != ";");	// Exit loop once a ';' is found

            ifile3 << ";\n";	// Finish "var" rule by including this string

        }


            // Rule for keyword "begin"
        else if (vector_given_tokens[y] == "begin") {
            ifile3 << "int main()" << "\n"		// Ouput main function to .cpp
                   << '{' << "\n\t";
            tabFlag = true;		                // Begin tabbing each line
        }


            // Rule for "show"
        else if (vector_given_tokens[y] == "show") {
            ifile3 << "cout << ";

            y += 2;		// Skip ahead two vector positions to bypass "show" and "("

            ifile3 << vector_given_tokens[y];

            y += 1;		// Skip ahead one vector position to bypass ")"

            ifile3 << ' ';
        }


            // Rule for ';'
        else if (vector_given_tokens[y] == ";" || vector_given_tokens[y] == "; ") {	// Question: Why do I need to check for "; "?
            ifile3 << ";\n";

            if (tabFlag == true && vector_given_tokens[y + 1] != "end")   	// tabFlag is true only after .cpp file has entered "int main() function.
                ifile3 << "\t";						// Second condition used so the last "}" is NOT tabbed.
        }


            // Rule for "end"
        else if (vector_given_tokens[y] == "end") {
            tabFlag = false;		// Reset tabFlag to false
            ifile3 << "}\n";		// Finish .cpp file
        }


        else
            ifile3 << vector_given_tokens[y] << ' ';
    }

    cout << "File filep3.cpp has been created.\n";

    ifile3.close();
}

#endif




