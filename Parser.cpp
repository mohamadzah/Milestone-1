//
// Created by user on 12/20/2019.
//

#include "Parser.h"
#include "ConditionParser.h"

/**
 * In this function we will execute all the commands we have in our map
 * We use an index to help us know how many tokens we need to skip in order to
 * execute the next command.
 */
void Parser::parser() {
    size_t index = 0;
    vector<string> arr;
    string pop;
    arr = _table->getArray();
    while (index < arr.size()-1) {
        pop = arr[index];
        pop.pop_back();
        if (hashMap.find(pop) != hashMap.end()) {
            Command * c = hashMap.find(pop)->second;
            index += c->execute(arr, index);
        }
    }
}

/**
 * Constructor.
 */

Parser::Parser(SymbolTable * table1) {
    this->_table = table1;
}

/**
 * In this function we will initialize our map that will include all the commands,
 * we check what type of command we have, and we add it to the map.
 *
 */

void Parser::setMap() {
    vector<string> arr;
    arr = _table->getArray();
    map<string, pair<string,double>> symTable = _table->getTable();
    string command;
    for (size_t i = 0; i < arr.size()-1; ++i) {
        command = arr[i];
        command.pop_back();
        if (command == "openDataServer") {
            hashMap.insert({command, new OpenServerCommand});
        } else if (command == "connectControlClient") {
            hashMap.insert({command, new ConnectCommand});
        } else if (command == "var") {
            hashMap.insert({command, new DefineVarCommand});
        } else if (_table->getKey(command)) {
            hashMap.insert({command, new SetVarCommand});
        } else if (command == "Sleep") {
            hashMap.insert({command, new SleepCommand});
        } else if (command == "if" || command == "while") {
            hashMap.insert({command, new ConditionParser});
        } else if (command == "Print") {
            hashMap.insert({command, new PrintCommand});
        }
    }
}
