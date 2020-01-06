//
// Created by user on 12/21/2019.
//
#include "iostream"
#include "Command.h"
#include <sys/types.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef FLIGHTGEAR_CONNECTCOMMAND_H
#define FLIGHTGEAR_CONNECTCOMMAND_H

//function to print the message to the server.
void print(string msg, double val);
//close socket function
void closeSocket();
/**
 * ConnectCommand
 *
 * Inherits from Command interface and implements it.
 *
 * */
class ConnectCommand : public Command {
public:
    static bool condition;
    ConnectCommand() = default;
    int execute(vector<string> array, int index) override;
    static void connectServer(vector<string> array, int index);
    ~ConnectCommand() override = default;
};

#endif //FLIGHTGEAR_CONNECTCOMMAND_H
