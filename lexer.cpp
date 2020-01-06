//
// Created by user on 12/18/2019.
//

#include "lexer.h"

using namespace std;
/**
 * Lexer file
 *
 * in this function we will divide the file's content into tokens, and each token ends with a ','
 * Because we want to easily distinguish between each token in order to help us create commands for execution.
 *
 * */
vector<string> lexerCommands(ifstream &file) {
    //we will save what given file contains in here in the right order.
    vector<string> array;
    string line;
    string lexerAdd;
    int t = 0;
    //we recieved an open file
    while (getline(file, line)) {
        for (int i = 0; i < line.length(); i++) {
            // if we reached a bracket closing or opening, space, or an equal symbol, that means
            // we have reached the end of a string that we want to add as a token.
            if (line[i] == '(' || line[i] == ')' || isspace(line[i]) || line[i] == '=') {
                //if we have a '=' alone, that means we are setting a value.
                if (line[i] == '=' && (line[i-1] != '<' && line[i-1] != '>' && line[i+1] != '=' && line[i-1] != '!')) {
                    if (lexerAdd.length() >= 1) {
                        lexerAdd += ',';
                        array.push_back(lexerAdd);
                    }
                    lexerAdd.clear();
                    lexerAdd += '=';
                    t = i;
                    //we break out of the loop, and proceed to the appropriate if condition after the foor loop.
                    break;
                }
                if (line[i] == '=' && (line[i-1] == '<' || line[i-1] == '>' || line[i-1] == '!' || line[i+1] == '=')) {
                    //if we have == for a conditional operation, we add it.
                    if (line[i+1] == '=') {
                        lexerAdd += "==";
                        i++;
                    } else {
                        lexerAdd += '=';
                    }
                }
                //we push the string if none of the above.
                if (lexerAdd.length() >= 1) {
                    lexerAdd += ',';
                    array.push_back(lexerAdd);
                }
                //clear the temporary string and continue.
                lexerAdd.clear();
                continue;
            }
            //keep adding chars to the string
            lexerAdd += line[i];
            //if the current word is Print or sleep, we break out of the loop and proceed to the appropriate condition after the loop.
            if (lexerAdd == "Print" || lexerAdd == "Sleep") {
                t = i;
                break;
            }

            if (i + 1 == line.length()) {
                if (lexerAdd.length() >= 1) {
                    lexerAdd += ',';
                    array.push_back(lexerAdd);
                    lexerAdd.clear();
                    continue;
                }
            }
        }
        //if we broke out of the loop from '=', we proceed here and add the next token to the vector
        if (lexerAdd == "=") {
            //if we are here, we will now add the value that comes after =
            lexerAdd += ',';
            array.push_back(lexerAdd);
            lexerAdd.clear();
            t++;
            while (t < line.length()) {
                if (line.length() == t+2) {
                    lexerAdd += line[t];
                    lexerAdd += ',';
                    array.push_back(lexerAdd);
                    lexerAdd.clear();
                }
                if (line[t] != ' ') {
                    lexerAdd += line[t];
                }
                t++;
            }
            lexerAdd.clear();
        }
        //if we broke out of the loop from sleep or print, we proceed here and add the next token to the vector
        if (lexerAdd == "Print" || lexerAdd == "Sleep") {
            t++;
            //we will add here whatever comes inbetween the brackets (e.g Print(--> this line <---))
            while (t < line.length()) {
                if (line[t] == '(' || line[t] == ')') {
                    if (lexerAdd.length() >= 1) {
                        lexerAdd += ',';
                        array.push_back(lexerAdd);
                        lexerAdd.clear();
                    }
                }
                if (line[t] != '(') {
                    lexerAdd += line[t];
                }
                t++;
            }
            lexerAdd.clear();
        }
    }
    return array;
}
