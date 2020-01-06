//
// Created by user on 12/21/2019.
//
#include "Command.h"
#include "DefineVarCommand.h"
#include "SetVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "SymbolTable.h"
#include "Interpreter.h"


#ifndef FLIGHTGEAR_CONDITIONPARSER_H
#define FLIGHTGEAR_CONDITIONPARSER_H

/**
 * ConditionParser class.
 *
 * This class inherits from the class command, and has to implement the function execute which
 * will execute the condition command.
 *
 */

class ConditionParser : public Command  {
public:
    ConditionParser();
    int execute(vector<string> array, int index) override;
    ~ConditionParser() override = default;
};

#endif //FLIGHTGEAR_CONDITIONPARSER_H
