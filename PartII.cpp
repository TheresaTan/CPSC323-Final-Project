

//
// Part II, Table I
//

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
//LIBRARY THAT IGNORES/TAKES OUT WHITE SPACES
#include <sstream>
#include <string>
//#include <ctype.h>
using namespace std;

//first and follow table
string table[22][19] = {

        //state  program                        integer   show(     ; var     begin    end     a-e     0-9       +        -        (        *         /        ,         :          );       =          ;    invalid
        /*P=0*/ {"program I; var D begin G end", "null", "null"   , "null"  , "null", "null", "null", "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*I=1*/ {"null"                        , "null", "null"   , "null"  , "null", "null", "LK"  , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*K=2*/ {"null"                        , "null", "null"   , "null  ", "null", "null", "LK"  , "JK"  , "null" , "null" , "null", "lambda", "lambda", "lambda", "lambda", "lambda", "lambda","lambda", "null"},
        /*D=3*/ {"null"                        , "null", "null"   , "null"  , "null", "null", "B:C;", "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*B=4*/ {"null"                        , "null", "null"   , "null"  , "null", "null", "IM"  , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*M=5*/ {"null"                        , "null", "null"   , "null"  , "null", "null", "null", "null", "null" , "null" , "null", "null"  , "null"  , ",IM"   , "lambda", "null"  , "null"  , "null" , "null"},
        /*C=6*/ {"null"                      ,"integer", "null"   , "null"  , "null", "null", "null", "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*G=7*/ {"null"                        , "null", "SU"     , "null"  , "null", "null", "SU"  , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*S=8*/ {"null"                        , "null", "W"      , "null"  , "null", "null", "A"   , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*W=9*/ {"null"                        , "null","show(I);", "null"  , "null", "null", "null", "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*A=10*/{"null"                        , "null", "null"   , "null"  , "null", "null", "I=E;", "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*E=11*/{"null"                        , "null", "null"   , "null"  , "null", "null", "TQ"  , "TQ"  , "TQ"   , "TQ"   , "TQ"  , "null"  , "null"  , "null"  , "null"  ,  "null" , "null"  , "null" , "null"},
        /*Q=12*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "null", "+TQ"  , "-TQ"  , "null", "null"  , "null"  , "null"  , "null"  ,"lambda", "null"  ,"lambda", "null"},
        /*T=13*/{"null"                        , "null", "null"   , "null"  , "null", "null", "FR"  , "FR"  , "FR"   , "FR"   , "FR"  , "null"  , "null"  , "null"  , "null"  ,"lambda", "null"  , "null" , "null"},
        /*R=14*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "null","lambda","lambda", "null", "*FR"   , "/FR"   , "null"  , "null"  ,"lambda", "null"  ,"lambda", "null"},
        /*F=15*/{"null"                        , "null", "null"   , "null"  , "null", "null", "I"   , "N"   , "N"    , "N"    , "(E)" , "null"  , "null"  , "null"  , "null"  ,"lambda", "null"  , "null" , "null"},
        /*N=16*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "JO"  , "HJO"  , "HJO"  , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*O=17*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "JO"  ,"lambda","lambda", "null","lambda" ,"lambda" , "null"  , "null"  , "null"  , "null"  ,"lambda", "null"},
        /*H=18*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null","lambda", "+"   , "-"    , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*J=19*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "0-9" , "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*L=20*/{"null"                        , "null", "null"   , "null"  , "null", "null", "a-e" , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*U=21*/{"null"                        , "null", "SU"     , "null"  , "null","lambda", "SU" , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"}

};
//vector_given_tokens is where you read the file,
//state_stack is where you push and pop the states to accept the file
vector<string> vector_given_tokens, state_stack;
//Keep track of elements in the state_stack(the popped element)
string state;
int row, column;

//Used to debug
void walk_stack(vector<string>);

//put tokens into a vector
void program_vector(vector<string>&);


//Assigns the rows and does state = [row][column]
//finds match for current state
//puts out error messages if null
vector<string> update_state(vector<string>, string&);

//Used to iterate individual letters in string e.g ab1, ce334, etc
//assigns the columns
void check_var(string);

//Used to iterate through reserved_words and other terminals
//assigns the columns
void check_word(string);

bool check_file_for_errors(vector<string>&);

bool check_spelling(string&);

int main(){

    //PUTTING TOKENS INTO A VECTOR
    program_vector(vector_given_tokens);
    walk_stack(vector_given_tokens);

    //the word read in the file
    string iter;
    //pushing first element onto the stack
    state_stack.push_back("P");


    cout << "Check for errors\n";
    //if true then there are automatic errors in the file
    bool errors = check_file_for_errors(vector_given_tokens);
    if(errors){
        cout << "Rejected.\n";
        return 0;
    }

    cout << "<START DEBUGGING FILE>\n";
    for(int i=0; i<vector_given_tokens.size(); i++){
        //pop top element in state_stack
        state = state_stack.back();
        state_stack.pop_back();
        cout <<"Pop: " << state << endl;
        iter = vector_given_tokens[i];
        cout << "Read: " << iter << endl;


        check_word(iter);

        if(state == "null") break;


    }



    if(state != "null") cout << "No error.\nAccepted!";
    else cout << "Rejected.\n";


    return 0;
}


void walk_stack(vector<string> state_stack){
    vector<string> temp = state_stack;
    cout << "Current Stack: ";
    for(auto it = temp.begin(); it < temp.end(); it++){
        cout << *it << " \t";
    }
    cout << endl;
}



void program_vector(vector<string>& vector_given_tokens) {
    // CREATING TOKENS AND PLACING THEM IN A VECTOR
    fstream filename;
    //used my files path to find the file
    //THIS PATH WILL NOT WORK ON SOMEONE ELSES COMPUTER
    filename.open("/Users/Theresa/CLionProjects/untitled13/filep2.txt");

    if (!filename.is_open()) {
        cout << "filep2.txt not found...\n";
        //PAUSE
    }else cout << "\nfilep2.txt FOUND!\n";


    string str_line;
    string word;
    //using istringstream to split up words in the line while ignoring white spaces
    while (!filename.eof()) {
        getline(filename, str_line);
        //IGNORES OUT WHITE SPACES
        istringstream iss(str_line);

        while(iss >> word){
            vector_given_tokens.push_back(word);
        }
    }

    //system("pause");


}

bool check_file_for_errors(vector<string>& vector_given_tokens){
    //counters for the parentheses
    int counter1 = 0, counter2 = 0;
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
            counter1++;
        }else if(vector_given_tokens[i] == ")"){
            
            //counts right parentheses
            counter2++;
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
                //put : and integer in case one of them is missing from the file
                if(vector_given_tokens[i] == ":" || vector_given_tokens[i] == "integer"){
                    dec_list_done = true;
                }
                
                //pushes back only the variables and no punctuation marks
                if(vector_given_tokens[i] != "," && vector_given_tokens[i] != ":") {
                    temp.push_back(vector_given_tokens[i]);
                }
                i++;
            }
            cout << "Temp stack\n";
            walk_stack(temp);
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
                    check_expression = vector_given_tokens[k+1];
                    auto it2 = check_expression.begin();
                    if( (*it2 >= 'a' && *it2 <= 'e') || *it2 == '(' || (*it2 >= '0' && *it2 <= '9')){
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
    if(counter1 < counter2){
        cout << endl;
        cout << "(\t Left Parentheses is missing.\n";
        return true;
    }else if(counter2 < counter1){
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
}

void check_var(string iter){
    auto it = iter.begin();
    string letter;
    //assigning and matching for each letter in the word to match
    do{
        //a-e is column = 6 and 0-9 is column 7
        switch(*it){
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e': column = 6; break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': column = 7; break;

        }

        cout <<"Pop: " << state << endl;
        cout <<"Looking for: " << *it << endl;
        //making char a string
        letter = *it;
        state_stack = update_state(state_stack, letter);
        it++;

    }while(it != iter.end() && state != "null");
}


void check_word(string iter){

    //assigning columns
    if(iter == "program"){
        column = 0;
        state_stack = update_state(state_stack, iter);
    }else if(iter == "integer"){
        column = 1;
        state_stack = update_state(state_stack, iter);
    }else if(iter == "show"){
        column = 2;
        state_stack = update_state(state_stack, iter);
    }else if(iter  == "var"){
        column = 3;
        state_stack = update_state(state_stack, iter);
    }else if(iter  == "begin"){
        column = 4;
        state_stack = update_state(state_stack, iter);
    }else if(iter  == "end"){
        column = 5;
        state_stack = update_state(state_stack, iter);
    }else if(iter == "+"){
        column = 8;
        state_stack = update_state(state_stack, iter);
    }else if(iter == "-"){
        column = 9;
        state_stack = update_state(state_stack, iter);
    }else if(iter  == "("){
        column = 10;
        state_stack = update_state(state_stack, iter);
    }else if(iter  == "*"){
        column = 11;
        state_stack = update_state(state_stack, iter);
    }else if(iter == "/"){
        column = 12;
        state_stack = update_state(state_stack, iter);
    }else if(iter  == ","){
        column = 13;
        state_stack = update_state(state_stack, iter);
    }else if(iter == ":"){
        column = 14;
        state_stack = update_state(state_stack, iter);
    }else if(iter == ")"){
        column = 15;
        state_stack = update_state(state_stack, iter);
    }else if(iter == "="){
        column = 16;
        state_stack = update_state(state_stack, iter);
    }else if(iter == ";"){
        column = 17;
        state_stack = update_state(state_stack, iter);
    }else{//this checks the individual letters and ints in the variable e.g. ab1, e33a, b16
        check_var(iter);

    }

}



vector<string> update_state(vector<string> state_stack, string& iter){
    bool word_match = false;
    while(!word_match) {
        //assigning the row and reading the table with row and column
        if (state == "A") {
            row = 10;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "B") {
            row = 4;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "C") {

            row = 6;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "D") {

            row = 3;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "E") {

            row = 11;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "F") {

            row = 15;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "G") {

            row = 7;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "H") {

            row = 18;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "I") {
            row = 1;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "J") {

            row = 19;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "K") {

            row = 2;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "L") {

            row = 20;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "M") {

            row = 5;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "N") {

            row = 16;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "O") {

            row = 17;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "P") {
            row = 0;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "Q") {

            row = 12;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "R") {

            row = 14;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "S") {

            row = 8;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "T") {

            row = 13;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "U") {

            row = 21;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        } else if (state == "W") {

            row = 9;
            cout << "[" << state << "][";
            cout << iter << "] = ";
            state = table[row][column];
            cout << state << endl;
        }


        if (state == iter) {
            cout << "Successful match: " << iter << endl;
            walk_stack(state_stack);
            word_match = true;
        } else if (state == "program I; var D begin G end") {   //pushing back elements from the table into the state_stack

            state_stack.push_back("end");
            state_stack.push_back("G");
            state_stack.push_back("begin");
            state_stack.push_back("D");
            state_stack.push_back("var");
            state_stack.push_back(";");
            state_stack.push_back("I");
            state_stack.push_back("program");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;
        } else if (state == "LK") {
            state_stack.push_back("K");
            state_stack.push_back("L");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;
        } else if (state == "JK") {
            state_stack.push_back("K");
            state_stack.push_back("J");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;
        } else if (state == "B:C;") {
            state_stack.push_back(";");
            state_stack.push_back("C");
            state_stack.push_back(":");
            state_stack.push_back("B");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "IM") {
            state_stack.push_back("M");
            state_stack.push_back("I");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;
        } else if (state == ",IM") {
            state_stack.push_back("M");
            state_stack.push_back("I");
            state_stack.push_back(",");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;
        } else if (state == "SU") {
            state_stack.push_back("U");
            state_stack.push_back("S");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;
        } else if (state == "W") {
            state_stack.push_back("W");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;
        } else if (state == "A") {
            state_stack.push_back("A");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;
        } else if (state == "show(I);") {
            state_stack.push_back(";");
            state_stack.push_back(")");
            state_stack.push_back("I");
            state_stack.push_back("(");
            state_stack.push_back("show");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;
        } else if (state == "I=E;") {
            state_stack.push_back(";");
            state_stack.push_back("E");
            state_stack.push_back("=");
            state_stack.push_back("I");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "TQ") {
            state_stack.push_back("Q");
            state_stack.push_back("T");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "+TQ") {
            state_stack.push_back("Q");
            state_stack.push_back("T");
            state_stack.push_back("+");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "-TQ") {
            state_stack.push_back("Q");
            state_stack.push_back("T");
            state_stack.push_back("-");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "FR") {
            state_stack.push_back("R");
            state_stack.push_back("F");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "*FR") {
            state_stack.push_back("R");
            state_stack.push_back("F");
            state_stack.push_back("*");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "/FR") {
            state_stack.push_back("R");
            state_stack.push_back("F");
            state_stack.push_back("/");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "I") {
            state_stack.push_back("I");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "N") {
            state_stack.push_back("N");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "(E)") {
            state_stack.push_back(")");
            state_stack.push_back("E");
            state_stack.push_back("(");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "JO") {
            state_stack.push_back("O");
            state_stack.push_back("J");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "HJO") {
            state_stack.push_back("O");
            state_stack.push_back("J");
            state_stack.push_back("H");
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "lambda") {
            walk_stack(state_stack);
            state = state_stack.back();
            state_stack.pop_back();
            cout << "Pop: " << state << endl;

        } else if (state == "a-e") {
            if (iter >= "a" && iter <= "e") {
                cout << "Successful Match: " << iter << endl;
                walk_stack(state_stack);
                state = state_stack.back();
                state_stack.pop_back();

                word_match = true;
            }
        } else if (state == "0-9") {
            if (iter >= "0" && iter <= "9") {
                cout << "Successful Match: " << iter << endl;
                walk_stack(state_stack);
                state = state_stack.back();
                state_stack.pop_back();
                word_match = true;
            }
        }else if (state == "null") {    //finding errors and putting out error messages for states that were pushed on the stack but not on the file
            if(iter >= "a" && iter <= "e" && row == 5){
                cout << ",\tis expected\n";
                break;
            }else if(row == 14 && iter >= "a" && iter <= "e" && state >= "0" && state <= "9"){
                cout << "Invalid variable\n";
                break;
            }else if(row == 14){
                cout << ";\tis expected\n";
                break;
            }else if (iter == "begin") {
                cout << iter << "\tis expected\n";
                break;
            } else if (iter == "integer" && (row == 5)) {
                cout << ":\tis expected\n";
                break;
            } else if (row == 21 && iter == "=") {
                cout << "Invalid Expression: Missing Variable\n";
                break;
            } else if(row == 21){
                if(!check_spelling(iter)){
                    cout << "show\t is expected\n";

                }
                break;
            }else if(row == 3 && iter == "integer"){
                cout << ":\t is expected\n";
                break;
            } else if(row==6){
                if(!check_spelling(iter)){
                    cout << "integer\t is expected\n";

                }
                break;
            }else if(row ==1){
                cout << "Unknown Identifier\n";
                break;
            }else if(row == 7){
                cout << "Invalid Expression:\tMissing Variable\n";
                break;
            }else if(row == 11){
                cout << "invalid Expression:\tMissing Expression\n";
                break;
            }
            break;
        }else if(state =="var" && iter != "var"){   //these errors are for states that weren't pushed on the stack and made errors
            cout << state << "\tis expected\n";
            state = "null";
            break;
        }else if(state =="begin" && iter != "begin"){
            cout << state << "\tis expected\n";
            state = "null";
            break;
        }else if(state =="(" && iter != "("){
            cout << state << "\tis expected\n";
            state = "null";
            break;
        }else if(state ==")" && iter != ")"){
            cout << state << "\tis expected\n";
            state = "null";
            break;
        }else if(state =="," && iter != ","){
            cout << state << "\tis expected\n";
            state = "null";
            break;
        }else if(state ==":" && iter != ":"){
            cout << state << "\tis expected\n";
            state = "null";
            break;
        }else if(state =="=" && iter != "="){
            cout << state << "\tis expected\n";
            state = "null";
            break;
        }else if(state ==";" && iter != ";"){
            cout << state << "\tis expected\n";
            state = "null";
            break;
        }else {
            state = "null";
            break;
        }



    }

    return state_stack;
}


