//
// Created by user on 12/22/2019.
//

#include "PrintCommand.h"

#include <utility>
#include "DefineVarCommand.h"
#include "OpenServerCommand.h"

/**
 * In this function we print a token from the vector,
 *
 * We check whether we have a variable value that we need to print, or just a normal text.
 *
 */

int PrintCommand::execute(vector<string> array, int index) {
    auto * v = new DefineVarCommand();
    //we will check the print if we will print a normal string or a var!
    string check = array[index+1];
    check.pop_back();
    if (SymbolTable::getKey(check)) {
        //we have a var and we will print var, here we call function and send var name
        //we get value from simulator at runtime.
        //if we are here, we will have to print a variable value from the symbolTable
        map<string, string> mapC = v->returnMap();
        if (mapC.find(check) != mapC.end()) {
            auto k = mapC.find(check)->second;
            double val = SymbolTable::symTable.find(k)->second.second;
            cout << val << endl;
        }
        return 2;
    } else {
        //we call the normal print function with the value we want to print.
        normalPrint(check);
        return 2;
    }
}
/**
 * Print a normal string.
 */

void PrintCommand::normalPrint(string str) {
    string temp = std::move(str);
    temp.pop_back();
    temp.erase(0, 1);
    cout << temp << endl;
}

PrintCommand::PrintCommand() {}