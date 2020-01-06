//
// Created by mohamad on 26/12/2019.
//

#ifndef FLIGHTGEAR_SLEEPCOMMAND_H
#define FLIGHTGEAR_SLEEPCOMMAND_H

#include "Command.h"
#include <thread>
#include <iostream>
/**
 * SleepCommand header file.
 *
 * This class implements the Command interface, where we implement the execute function.
 *
 */

class SleepCommand : public Command {
public:
    SleepCommand();
    int execute(vector<string> array, int index) override;
    ~SleepCommand() override = default;
};

#endif //FLIGHTGEAR_SLEEPCOMMAND_H
