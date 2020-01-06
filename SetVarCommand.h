//
// Created by user on 12/21/2019.
//

#ifndef FLIGHTGEAR_SETVARCOMMAND_H
#define FLIGHTGEAR_SETVARCOMMAND_H

#include "DefineVarCommand.h"
//function that checks if a string is a number or not.
bool isnt_number(const std::string& s);

class SetVarCommand : public DefineVarCommand {
public:
    SetVarCommand() = default;
    int execute(vector<string> array, int index) override;
    ~SetVarCommand() override = default;
};


#endif //FLIGHTGEAR_SETVARCOMMAND_H
