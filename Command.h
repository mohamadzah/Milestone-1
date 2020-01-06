//
// Created by user on 12/19/2019.
//
#include <vector>
#include <string>

#ifndef FLIGHTGEAR_COMMAND_H
#define FLIGHTGEAR_COMMAND_H

using namespace std;

/**
 * Command Interface
 *
 * The interface which all the different commands we have will implement.
 */

class Command {
public:
    //the execute function that will execute the command.
    virtual int execute(vector<string> array, int index) = 0;
    virtual ~Command() = default;
};

#endif //FLIGHTGEAR_COMMAND_H
