//
// Created by user on 12/21/2019.
//

#include <map>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <thread>
#include <list>
#include <functional>
#include "Command.h"
#include "SymbolTable.h"

#ifndef FLIGHTGEAR_DEFINEVARCOMMAND_H
#define FLIGHTGEAR_DEFINEVARCOMMAND_H

/**
 * DefineVarCommand
 *
 * Inherits from Command interface and implements it.
 *
 * */
class DefineVarCommand : public Command, public SymbolTable {
protected:
    static map<string, string> mapC;
public:
    DefineVarCommand() = default;
    static map<string, string> returnMap();
    int execute(vector<string> array, int index) override;
    ~DefineVarCommand() override = default;
};

#endif //FLIGHTGEAR_DEFINEVARCOMMAND_H
