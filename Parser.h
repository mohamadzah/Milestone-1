//
// Created by user on 12/20/2019.
//

#include <map>
#include <string>
#include <unordered_map>
#include <iostream>
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "SetVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"

#ifndef FLIGHTGEAR_PARSER_H
#define FLIGHTGEAR_PARSER_H

using namespace std;
/**
 * Parser
 *
 * In the parser we will create and execute all commands.
 *
 * */
class Parser {
protected:
    //class fields
    SymbolTable * _table;
    map<string,class Command*> hashMap;
public:
    void parser();
    void setMap();
    explicit Parser(SymbolTable * table1);
};

#endif //FLIGHTGEAR_PARSER_H
