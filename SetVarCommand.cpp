//
// Created by user on 12/20/2019.
//
#include "Command.h"
#include "SetVarCommand.h"
#include "DefineVarCommand.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"
#include "Interpreter.h"
#define MINUS '-'
#define PLUS '+'
#define MULT '*'
#define SUB '/'
#include "sstream"


/**
 * checks whether a string contains mathematicals operators or not.
 */
bool isnt_number(const std::string& s)
{
    return s.find(MINUS) != std::string::npos || s.find(PLUS) != std::string::npos ||
           s.find(MULT) != std::string::npos || s.find(SUB) != std::string::npos;
}

/**
 * In this function we will send the path and the value we want to the print function
 * that sends a message to the server.
 */

int SetVarCommand::execute(vector<string> array, int index) {
    map<string, string> mapC = returnMap();
    string serverWrite;
    string setV,setVar;
    setV = array[index];
    setV.pop_back();
    //here we will write to the server
    if (mapC.find(setV) != mapC.end() && ((index + 4) < (array.size()-1))) {
        serverWrite += mapC.find(setV)->second;
        serverWrite+= " ";
        //here is our expression.
        setVar = array[index + 2];
        setVar.pop_back();
        //here we are setting a value for a var. if we have a normal number, we set it, if not we create an expression.
        //as we are evaluating the expression, we assign the current value in the symboltable
        if (isnt_number(setVar)) {
            Interpreter* i = new Interpreter();
            Expression *e = nullptr;
            e = i->interpret(setVar);
            double val = e->calculate();
            print(serverWrite, val);
        } else {
            stringstream ss;
            double var;
            ss << setVar;
            ss >> var;
            print(serverWrite, var);
        }
    }
    int i = 3;
    return i;
}


