//
// Created by user on 12/21/2019.
//
#include "ConnectCommand.h"
#include <thread>
#include "SetVarCommand.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <utility>
#include "Interpreter.h"
#include <cmath>
#include "sstream"

/**
 * ConnectCommand file
 *
 * In this file we implement the execute function , which creates a thread that executes the connectServer
 * function, in the connectServer function we will create a connection to the server with a host address
 * and a port,
 *
 * The print function is a global function that sends a message to the simulator
 *
 */

thread thread2;

int client_socket = socket(AF_INET, SOCK_STREAM, 0);

int ConnectCommand::execute(vector<string> array, int index) {
    thread2 = thread(connectServer, array, index);
    thread2.detach();
    return 2;
}

void closeSocket() {
    close(client_socket);
}

void print(string msg, double val) {
    string writeM = "set " + msg + "" + to_string(val)+ "\r\n";
    ssize_t return_val;
    return_val = write(client_socket, writeM.c_str(), writeM.length());
    if (return_val == -1) {
        std::cout << "Error sending message" << std::endl;
    }
};

void ConnectCommand::connectServer(vector<string> array, int index) {
    //create socket
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        exit(1);
    }
    //We need to create a sockaddr obj to hold address of server
    string port = array[index + 1];
    port.pop_back();

    size_t find = port.find(',');
    string adrs = port.substr(0,find);
    adrs.pop_back();
    adrs.erase(0,1);

    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(adrs.c_str());
    string port2 = port.substr(find + 1);
    //check the state of the input (expression or not)
    if (isnt_number(port2)) {
        auto *i = new Interpreter();
        Expression *e = nullptr;
        e = i->interpret(port2);
        double val = e->calculate();
        int x = round(val);
        address.sin_port = htons(x);
    } else {
        address.sin_port = htons(stoi(port2));
    }
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.
    // Requesting a connection with the server on address and port
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        closeSocket();
        exit (1);
    }
}

