//
// Created by user on 12/22/2019.
//

#ifndef FLIGHTGEAR_PRINTCOMMAND_H
#define FLIGHTGEAR_PRINTCOMMAND_H

#include "Command.h"
#include "SymbolTable.h"
#include "ConnectCommand.h"
/**
 * PrintCommand
 *
 * Inherits from Command interface and implements it.
 *
 * */
class PrintCommand : public Command {
public:
    PrintCommand();
    int execute(vector<string> array, int index) override;
    void normalPrint(string str);
    ~PrintCommand() override = default;
};

#endif //FLIGHTGEAR_PRINTCOMMAND_H
