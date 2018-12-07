#include <iostream>
#include <fstream>		//file reading
#include <string>
#include <vector>

#include "VectorString.h"		// Header file

using namespace std;

int main() {
	//ideas:
	//	use parsing tokens to break up non white space substrings and then space them out ex token_n + ' ' + token_n+1

	vector<string> vector_given_tokens;

	// CREATING TOKENS AND PLACING THEM IN A VECTOR
	program_vector(vector_given_tokens);

	//	VECTOR POPULATION CHECK		PASSED
	//cout << "\n\tTOKEN VECTOR POPULATION CHECK\n\n";
	//for (int x = 0; x < vector_given_tokens.size(); x++) {	//	VECTOR POPULATION CHECK
	//	cout << x << ":\t" << vector_given_tokens[x] << "\n";
	//}

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

	cout << "File filep3.cpp has been created.";

	ifile3.close();

	PAUSE
		return 0;
}
