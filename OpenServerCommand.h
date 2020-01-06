//
// Created by user on 12/21/2019.
//
#ifndef FLIGHTGEAR_OPENSERVERCOMMAND_H
#define FLIGHTGEAR_OPENSERVERCOMMAND_H

#include <map>
#include <unordered_map>

/**
 * OpenServerCommand
 *
 * Inherits from Command interface and implements it.
 * Here we will open a socket and open the server.\
 *
 */

void closeSocketServer();

class OpenServerCommand : public Command {
public:
    //fields
    static map<string,double> variables;
    static vector<std::string> insertOrder;
public:
    OpenServerCommand() = default;
    int execute(vector<string> array, int index) override;
    static void openServer(vector<string> array, int index);
    ~OpenServerCommand() override = default;
};

#endif //FLIGHTGEAR_OPENSERVERCOMMAND_H
