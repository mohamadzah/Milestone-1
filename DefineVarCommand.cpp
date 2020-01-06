//
// Created by user on 12/19/2019.
//

#include <map>
#include <algorithm>
#include <list>
#include "Command.h"
#include "SymbolTable.h"
#include "DefineVarCommand.h"
#include "ConnectCommand.h"
#include "Interpreter.h"
#include <sstream>

map<string, string> DefineVarCommand::mapC;
/**
 * DefineVarCommand file
 *
 * In this file , we implement the execute function that is inherited from command interface
 * In the execute function, we will add a variable to the definevarcommand hashmap or the
 * SymbolTable according to the input, we will check the type of var we have, whether it is a variable
 * that contains a value from the simulator, or a variable that isn't directly related to it.
 *
 * */

int DefineVarCommand::execute(vector<string> array, int index) {
    SymbolTable* symbolTable = new SymbolTable(array);
    symbolTable->setMapKeys();
    string com;
    //check if the current token is var,
    if (array[index] == "var,") {
        com = array[index + 1];
        com.pop_back();
            //if we have to set value to simulator
            if (array[index + 2] == "->,") {
                if (array[index + 3] == "sim,") {
                    string line;
                    string commaRemove;
                    commaRemove = array[index + 4];
                    //remove the "" and the , from the token.
                    commaRemove.pop_back();
                    commaRemove.pop_back();
                    commaRemove.erase(0,1);
                    line += commaRemove;
                    //insert the var name with the line we have to send to the simulator
                    DefineVarCommand::mapC.insert({com, line});
                }
                //or if we have to get a value from the simulator.
            } else if (array[index + 2] == "<-,") {
                if (array[index + 3] == "sim,") {
                    string commaRemove;
                    commaRemove = array[index + 4];
                    //remove the "" and the , from the token.
                    commaRemove.pop_back();
                    commaRemove.pop_back();
                    commaRemove.erase(0,1);
                    string line;
                    line += commaRemove;
                    //insert the var name with the line we have to send to the simulator
                    DefineVarCommand::mapC.insert({com, line});
                }
            } else if (array[index+2] == "=,") {
                int i = 0, flag = 0;
                //if we are here, we have a variable that is not directly related to the simulator
                //so we will define it, and execute it at the same time. we will add it to the symbol table.
                string value = array[index+3];
                value.pop_back();
                //first we check if the value is a variable from simulator table
                auto findK = find(SymbolTable::keys.begin(), SymbolTable::keys.end(), value);
                if (findK != SymbolTable::keys.end()) {
                    auto val = SymbolTable::symTable.find(value)->second.second;
                    SymbolTable::addNewKey("var", com, val);
                    return 4;
                } else {
                    //or if it is an expression.
                    while (i < value.length()) {
                        if (isalpha(value[i])) {
                            flag = 1;
                        }
                        i++;
                    }
                    if (flag == 1) {
                        auto* i = new Interpreter();
                        Expression *e = nullptr;
                        e = i->interpret(value);
                        double val = e->calculate();
                        SymbolTable::addNewKey("var", com, val);
                        return 4;
                    } else {
                        //or if it is just a normal mathematical value.
                        stringstream ss;
                        double var;
                        ss << value;
                        ss >> var;
                        SymbolTable::addNewKey("var", com, var);
                        return 4;
                    }
                }
            }
        }
    int k = 5;
    return k;
}
//function to return the map.
map<string, string> DefineVarCommand::returnMap() {
    return DefineVarCommand::mapC;
}


