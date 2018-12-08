

//
// Main CPP file with Part II functions
//

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
//LIBRARY THAT IGNORES/TAKES OUT WHITE SPACES
#include <sstream>
#include <string>
#include <stdlib.h>
#include "VectorString.h"

using namespace std;

//first and follow table
string table[22][19] = {

        //state  program                        integer   show(     ; var     begin    end     a-e     0-9       +        -        (        *         /        ,         :          );       =          ;    invalid
        /*P=0*/ {"program I; var D begin G end", "null", "null"   , "null"  , "null", "null", "null", "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*I=1*/ {"null"                        , "null", "null"   , "null"  , "null", "null", "LK"  , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*K=2*/ {"null"                        , "null", "null"   , "null  ", "null", "null", "LK"  , "JK"  ,"lambda","lambda", "null", "lambda", "lambda", "lambda", "lambda", "lambda", "lambda","lambda", "null"},
        /*D=3*/ {"null"                        , "null", "null"   , "null"  , "null", "null", "B:C;", "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*B=4*/ {"null"                        , "null", "null"   , "null"  , "null", "null", "IM"  , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*M=5*/ {"null"                        , "null", "null"   , "null"  , "null", "null", "null", "null", "null" , "null" , "null", "null"  , "null"  , ",IM"   , "lambda", "null"  , "null"  , "null" , "null"},
        /*C=6*/ {"null"                      ,"integer", "null"   , "null"  , "null", "null", "null", "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*G=7*/ {"null"                        , "null", "SU"     , "null"  , "null", "null", "SU"  , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*S=8*/ {"null"                        , "null", "W"      , "null"  , "null", "null", "A"   , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*W=9*/ {"null"                        , "null","show(I);", "null"  , "null", "null", "null", "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*A=10*/{"null"                        , "null", "null"   , "null"  , "null", "null", "I=E;", "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*E=11*/{"null"                        , "null", "null"   , "null"  , "null", "null", "TQ"  , "TQ"  , "TQ"   , "TQ"   , "TQ"  , "null"  , "null"  , "null"  , "null"  ,  "null" , "null"  , "null" , "null"},
        /*Q=12*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "null", "+TQ"  , "-TQ"  , "null", "null"  , "null"  , "null"  , "null"  , "lambda", "null"  ,"lambda", "null"},
        /*T=13*/{"null"                        , "null", "null"   , "null"  , "null", "null", "FR"  , "FR"  , "FR"   , "FR"   , "FR"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*R=14*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "null","lambda","lambda", "null", "*FR"   , "/FR"   , "null"  , "null"  , "lambda", "null"  ,"lambda", "null"},
        /*F=15*/{"null"                        , "null", "null"   , "null"  , "null", "null", "I"   , "N"   , "N"    , "N"    , "(E)" , "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*N=16*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "JO"  , "HJO"  , "HJO"  , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*O=17*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "JO"  ,"lambda","lambda", "null","lambda" ,"lambda" , "null"  , "null"  ,"lambda" , "null"  ,"lambda", "null"},
        /*H=18*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null","lambda", "+"   , "-"    , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*J=19*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "0-9" , "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*L=20*/{"null"                        , "null", "null"   , "null"  , "null", "null", "a-e" , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*U=21*/{"null"                        , "null", "SU"     , "null"  , "null","lambda", "SU" , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"}

};
//vector_given_tokens is where you read the file,
//state_stack is where you push and pop the states to accept the file
vector<string> state_stack;
//Keep track of elements in the state_stack(the popped element)
string state;
int row, column;


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



int main(){

    //PART I
    if (remove("finalp2.txt") == 0) {
        cout << "\n\n\tPrevious finalp2.txt file found and deleted\n\n";
        //PAUSE
          //      system("cls");

    }

    string file_contents;

    readfile(file_contents);

    vector<string> vector_given_tokens;

    // CREATING TOKENS AND PLACING THEM IN A VECTOR

    program_vector(vector_given_tokens);

    //<DEBUGGING STACK>
    //walk_stack(vector_given_tokens);



    cout << "Starting Part II.\n";

    //this string will be used for the words read in the file
    string iter;
    //pushing first element onto the stack
    state_stack.push_back("P");

    //if true then there are automatic errors in the file e.g. program or end missing, etc.
    bool errors = check_file_for_errors(vector_given_tokens);
    if(errors){
        cout << "Rejected.\n";
        return 0;
    }

    cout << "<READING PROGRAM>\n";
    for(int i=0; i<vector_given_tokens.size(); i++){
        //pop top element in state_stack
        state = state_stack.back();
        state_stack.pop_back();
        iter = vector_given_tokens[i];


        check_word(iter);

        if(state == "null") break;


    }



    if(state != "null") {
        cout << "No error.\nAccepted!\n";
        create_cpp_file(vector_given_tokens);

    } else cout << "Rejected. Cannot move on to Part III\n";


    return 0;
}



//PART II FUNCTIONS




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
            state = table[row][column];
        } else if (state == "B") {
            row = 4;
            state = table[row][column];
        } else if (state == "C") {
            row = 6;
            state = table[row][column];
        } else if (state == "D") {
            row = 3;
            state = table[row][column];
        } else if (state == "E") {
            row = 11;
            state = table[row][column];
        } else if (state == "F") {
            row = 15;
            state = table[row][column];
        } else if (state == "G") {
            row = 7;
            state = table[row][column];
        } else if (state == "H") {
            row = 18;
            state = table[row][column];
        } else if (state == "I") {
            row = 1;
            state = table[row][column];
        } else if (state == "J") {
            row = 19;
            state = table[row][column];
        } else if (state == "K") {
            row = 2;
            state = table[row][column];
        } else if (state == "L") {
            row = 20;
            state = table[row][column];
        } else if (state == "M") {
            row = 5;
            state = table[row][column];
        } else if (state == "N") {
            row = 16;
            state = table[row][column];
        } else if (state == "O") {
            row = 17;
            state = table[row][column];
        } else if (state == "P") {
            row = 0;
            state = table[row][column];
        } else if (state == "Q") {
            row = 12;
            state = table[row][column];
        } else if (state == "R") {
            row = 14;
            state = table[row][column];
        } else if (state == "S") {
            row = 8;
            state = table[row][column];
        } else if (state == "T") {
            row = 13;
            state = table[row][column];
        } else if (state == "U") {
            row = 21;
            state = table[row][column];
        } else if (state == "W") {
            row = 9;
            state = table[row][column];
        }

        if (state == iter) {//SUCCESSFUL MATCH
            cout << "Successful match: " << iter << endl;
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
            state = state_stack.back();
            state_stack.pop_back();
        } else if (state == "LK") {
            state_stack.push_back("K");
            state_stack.push_back("L");
            state = state_stack.back();
            state_stack.pop_back();
        } else if (state == "JK") {
            state_stack.push_back("K");
            state_stack.push_back("J");
            state = state_stack.back();
            state_stack.pop_back();
        } else if (state == "B:C;") {
            state_stack.push_back(";");
            state_stack.push_back("C");
            state_stack.push_back(":");
            state_stack.push_back("B");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "IM") {
            state_stack.push_back("M");
            state_stack.push_back("I");
            state = state_stack.back();
            state_stack.pop_back();
        } else if (state == ",IM") {
            state_stack.push_back("M");
            state_stack.push_back("I");
            state_stack.push_back(",");
            state = state_stack.back();
            state_stack.pop_back();
        } else if (state == "SU") {
            state_stack.push_back("U");
            state_stack.push_back("S");
            state = state_stack.back();
            state_stack.pop_back();
        } else if (state == "W") {
            state_stack.push_back("W");
            state = state_stack.back();
            state_stack.pop_back();
        } else if (state == "A") {
            state_stack.push_back("A");
            state = state_stack.back();
            state_stack.pop_back();
        } else if (state == "show(I);") {
            state_stack.push_back(";");
            state_stack.push_back(")");
            state_stack.push_back("I");
            state_stack.push_back("(");
            state_stack.push_back("show");
            state = state_stack.back();
            state_stack.pop_back();
        } else if (state == "I=E;") {
            state_stack.push_back(";");
            state_stack.push_back("E");
            state_stack.push_back("=");
            state_stack.push_back("I");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "TQ") {
            state_stack.push_back("Q");
            state_stack.push_back("T");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "+TQ") {
            state_stack.push_back("Q");
            state_stack.push_back("T");
            state_stack.push_back("+");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "-TQ") {
            state_stack.push_back("Q");
            state_stack.push_back("T");
            state_stack.push_back("-");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "FR") {
            state_stack.push_back("R");
            state_stack.push_back("F");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "*FR") {
            state_stack.push_back("R");
            state_stack.push_back("F");
            state_stack.push_back("*");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "/FR") {
            state_stack.push_back("R");
            state_stack.push_back("F");
            state_stack.push_back("/");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "I") {
            state_stack.push_back("I");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "N") {
            state_stack.push_back("N");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "(E)") {
            state_stack.push_back(")");
            state_stack.push_back("E");
            state_stack.push_back("(");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "JO") {
            state_stack.push_back("O");
            state_stack.push_back("J");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "HJO") {
            state_stack.push_back("O");
            state_stack.push_back("J");
            state_stack.push_back("H");
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "lambda") {
            state = state_stack.back();
            state_stack.pop_back();

        } else if (state == "a-e") {
            if (iter >= "a" && iter <= "e") {
                cout << "Successful Match: " << iter << endl;
                state = state_stack.back();
                state_stack.pop_back();

                word_match = true;
            }
        } else if (state == "0-9") {
            if (iter >= "0" && iter <= "9") {
                cout << "Successful Match: " << iter << endl;
                state = state_stack.back();
                state_stack.pop_back();
                word_match = true;
            }
        }else if (state == "null") {    //finding errors and putting out error messages for states that were pushed on the stack but not on the file
            if(iter >= "a" && iter <= "e" && row == 5){
                cout << ",\tis missing\n";
                break;
            }else if(row == 14 && iter >= "a" && iter <= "e" && state >= "0" && state <= "9"){
                cout << "Invalid variable\n";
                break;
            }else if(row == 14){
                cout << ";\tis missing\n";
                break;
            }else if (iter == "begin") {
                cout << iter << "\tis expected\n";
                break;
            } else if (iter == "integer" && (row == 5)) {
                cout << ":\tis missing\n";
                break;
            } else if (row == 21 && iter == "=") {
                cout << "Invalid Expression: Missing Variable\n";
                break;
            } else if(row == 21){
                if(!check_spelling(iter)){
                    cout << "show\t is expected\n";

                }
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
        }else if(state =="," && iter != ","){
            cout << state << "\tis missing\n";
            state = "null";
            break;
        }else if(state ==":" && iter != ":"){
            cout << state << "\tis missing\n";
            state = "null";
            break;
        }else if(state =="=" && iter != "="){
            cout << state << "\tis missing\n";
            state = "null";
            break;
        }else if(state ==";" && iter != ";"){
            cout << state << "\tis missing\n";
            state = "null";
            break;
        }else {
            state = "null";
            break;
        }



    }

    return state_stack;
}



