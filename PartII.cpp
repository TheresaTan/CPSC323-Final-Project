
//
// Created by Theresa Tanubrata on 11/26/18.
//

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//first and follow table
string table[23][19] = {

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
        /*E=11*/{"null"                        , "null", "null"   , "null"  , "null", "null", "TQ"  , "TQ"  , "TQ"   , "TQ"   , "TQ"  , "null"  , "null"  , "null"  , "null"  ,"lambda" , "null"  , "null" , "null"},
        /*Q=12*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "null", "+TQ"  , "-TQ"  , "null", "null"  , "null"  , "null"  , "null"  ,"lambda", "null"  ,"lambda", "null"},
        /*T=13*/{"null"                        , "null", "null"   , "null"  , "null", "null", "FR"  , "FR"  , "FR"   , "FR"   , "FR"  , "null"  , "null"  , "null"  , "null"  ,"lambda", "null"  , "null" , "null"},
        /*R=14*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "null","lambda","lambda", "null", "*FR"   , "/FR"   , "null"  , "null"  ,"lambda", "null"  ,"lambda", "null"},
        /*F=15*/{"null"                        , "null", "null"   , "null"  , "null", "null", "I"   , "N"   , "N"    , "N"    , "(E)" , "null"  , "null"  , "null"  , "null"  ,"lambda", "null"  , "null" , "null"},
        /*N=16*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "JO"  , "HJO"  , "HJO"  , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*O=17*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "JO"  ,"lambda","lambda", "null","lambda" ,"lambda" , "null"  , "null"  , "null"  , "null"  ,"lambda", "null"},
        /*H=18*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null","lambda", "+"   , "-"    , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*J=19*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "0-9" , "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*L=20*/{"null"                        , "null", "null"   , "null"  , "null", "null", "a-e" , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*U=21*/{"null"                        , "null", "SU"     , "null"  , "null","lambda", "SU" , "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"},
        /*null*/{"null"                        , "null", "null"   , "null"  , "null", "null", "null", "null", "null" , "null" , "null", "null"  , "null"  , "null"  , "null"  , "null"  , "null"  , "null" , "null"}

};
vector<string> vector_given_tokens, state_stack;
string state;
int row, column, counter = 0;

void program_vector(vector<string>& vector_given_tokens) {
    // CREATING TOKENS AND PLACING THEM IN A VECTOR
    fstream filename;
    //used my files path to find the file
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
        istringstream iss(str_line);

        while(iss >> word){
            vector_given_tokens.push_back(word);
        }
    }


}


void walk_stack(vector<string> state_stack){
    vector<string> temp = state_stack;
    cout << "Current Stack: ";
    for(auto it = temp.begin(); it < temp.end(); it++){
        cout << *it << " \t";
    }
    cout << endl;
}

vector<string> update_state(vector<string> state_stack, string it){
    bool word_match = false;
    string iter = it;
    while(!word_match) {
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
        } else if (state == "program I; var D begin G end") {

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

                //it++;
                word_match = true;
            }
        } else if (state == "0-9") {
            if (iter >= "0" && iter <= "9") {
                cout << "Successful Match: " << iter << endl;
                walk_stack(state_stack);
                state = state_stack.back();
                state_stack.pop_back();
                //it++;
                word_match = true;
            }
        } else if (state == "null") {
            if (iter >= "a" && iter <= "b" && row == 0) {
                cout << "program is expected\n";
            } else if (iter == "var") {
                cout << iter << "\tis expected\n";
            } else if (iter == "begin") {
                cout << iter << "\tis expected\n";
            } else if (iter == "end") {
                cout << iter << "\tis expected\n";
            } else if (iter == "integer") {
                cout << iter << "\tis expected\n";
            } else if (iter == "show") {
                cout << iter << "\tis expected\n";
            } else if (iter == ":") {
                cout << iter << "\tis missing\n";
            } else if (iter == ",") {
                cout << iter << "\tis missing\n";
            } else if (iter == "(") {
                cout << iter << "\tLeft parantheses is missing\n";
            } else if (iter == ")") {
                cout << iter << "\tRight parantheses is missing\n";
            }
            break;
        } else break;



    }

    return state_stack;
}


void check_var(string iter){
    auto it = iter.begin();
    string letter;
    do{
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
            case '+': column = 8; break;
            case '-': column = 9; break;
            case '(': column = 10; break;
            case '*': column = 11; break;
            case '/': column = 12; break;
            case ',': column = 13; break;
            case ':': column = 14; break;
            case ')': column = 15; break;
            case '=': column = 16; break;
            case ';': column = 17; break;

        }

        cout <<"Pop: " << state << endl;
        cout <<"Iter: " << *it << endl;
        letter = *it;
        state_stack = update_state(state_stack, letter);
        it++;

    }while(it != iter.end() && state != "null");
}

void check_word(string iter){

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
    }else{
        check_var(iter);

    }

}


int main(){


    program_vector(vector_given_tokens);
    walk_stack(vector_given_tokens);

    //vector<string> state_stack;



    string word;
    string iter;
    state_stack.push_back("P");

    for(int i=0; i<vector_given_tokens.size(); i++){
        //walk_stack(state_stack);
        state = state_stack.back();
        state_stack.pop_back();
        cout <<"Pop: " << state << endl;
        iter = vector_given_tokens[i];
        cout << "Read: " << iter << endl;

        check_word(iter);

        counter++;

    }



    if(state != "null") cout << "No error.\n";
 //   }while(!state_stack.empty() && state != "null")


    return 0;
}
