//
// Created by user on 12/19/2019.
//
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include "Command.h"
#include <thread>
#include "OpenServerCommand.h"
#include "Interpreter.h"
#include "SetVarCommand.h"
#include <cmath>
#include <string.h>
#include <sstream>

//this is a subclass of command, here we will implement an execute function that will
//open a server port , which is what is required of this command.

/*The server-socket flow goes like this:
1- Create a socket
2- Bind our address to a requested address
3- Listen to incoming connections
4- Accept a connection
5- Write/read to and from the socket
6- Close the socket
*/

int socketSC = socket(AF_INET, SOCK_STREAM, 0);
static bool loop = false;
int newS;
map <string, double> OpenServerCommand::variables;
vector<string> OpenServerCommand::insertOrder;

int OpenServerCommand::execute(vector<string> array, int index) {
    thread thread1(openServer, array, index);
    while (!loop) {
    }
    thread1.detach();
    return 2;
}

/**
 * This function is the function is called throughout the program's life.
 * here we keep pushing the most recent values received from the simulator
 * into the symbolTable, that way we always get the most recent value.
 */

void run(const char * buffer) {
    double values[36];
    string temp;
    int iter = 0;
    //iterating over each char in the input
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] != ',')
            temp += buffer[i];
        //once we have the whole value we enter here and push it to values
        if (buffer[i + 1] == '\0' || buffer[i] == ',' || buffer[i + 1] == '\n') {
            values[iter] = atof(temp.c_str());
            iter++;
            temp.clear();
        }
    }
    int i = 0;
    //updating the values.
    for (const auto &x: OpenServerCommand::insertOrder) {
        OpenServerCommand::variables[x] = values[i];
        if (SymbolTable::getV(x)) {
            auto find = SymbolTable::symTable.find(x);
            find->second.second = values[i];
            i++;
        }
    }
}

void closeSocketServer() {
    close(newS);
    close(socketSC);
}

void OpenServerCommand::openServer(vector<string> array, int index) {
    //initiate map according to generic small.xml we were provided.
    insertOrder.push_back("/instrumentation/airspeed-indicator/indicated-speed-kt");
    variables["/instrumentation/airspeed-indicator/indicated-speed-kt"] = 0;
    insertOrder.push_back("/sim/time/warp");
    variables["/sim/time/warp"] = 1;
    insertOrder.push_back("/controls/switches/magnetos");
    variables["/controls/switches/magnetos"] = 2;
    insertOrder.push_back("/instrumentation/heading-indicator/offset-deg");
    variables["/instrumentation/heading-indicator/offset-deg"] = 3;
    insertOrder.push_back("/instrumentation/altimeter/indicated-altitude-ft");
    variables["/instrumentation/altimeter/indicated-altitude-ft"] = 4;
    insertOrder.push_back("/instrumentation/altimeter/pressure-alt-ft");
    variables["/instrumentation/altimeter/pressure-alt-ft"] = 5;
    insertOrder.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
    variables["/instrumentation/attitude-indicator/indicated-pitch-deg"] = 6;
    insertOrder.push_back("/instrumentation/attitude-indicator/indicated-roll-deg");
    variables["/instrumentation/attitude-indicator/indicated-roll-deg"] = 7;
    insertOrder.push_back("/instrumentation/attitude-indicator/internal-pitch-deg");
    variables["/instrumentation/attitude-indicator/internal-pitch-deg"] = 8;
    insertOrder.push_back("/instrumentation/attitude-indicator/internal-roll-deg");
    variables["/instrumentation/attitude-indicator/internal-roll-deg"] = 9;
    insertOrder.push_back("/instrumentation/encoder/indicated-altitude-ft");
    variables["/instrumentation/encoder/indicated-altitude-ft"] = 10;
    insertOrder.push_back("/instrumentation/encoder/pressure-alt-ft");
    variables["/instrumentation/encoder/pressure-alt-ft"] = 11;
    insertOrder.push_back("/instrumentation/gps/indicated-altitude-ft");
    variables["/instrumentation/gps/indicated-altitude-ft"] = 12;
    insertOrder.push_back("/instrumentation/gps/indicated-ground-speed-kt");
    variables["/instrumentation/gps/indicated-ground-speed-kt"] = 13;
    insertOrder.push_back("/instrumentation/gps/indicated-vertical-speed");
    variables["/instrumentation/gps/indicated-vertical-speed"] = 14;
    insertOrder.push_back("/instrumentation/heading-indicator/indicated-heading-deg");
    variables["/instrumentation/heading-indicator/indicated-heading-deg"] = 15;
    insertOrder.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
    variables["/instrumentation/magnetic-compass/indicated-heading-deg"] = 16;
    insertOrder.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
    variables["/instrumentation/slip-skid-ball/indicated-slip-skid"] = 17;
    insertOrder.push_back("/instrumentation/turn-indicator/indicated-turn-rate");
    variables["/instrumentation/turn-indicator/indicated-turn-rate"] = 18;
    insertOrder.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    variables["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = 19;
    insertOrder.push_back("/controls/flight/aileron");
    variables["/controls/flight/aileron"] = 20;
    insertOrder.push_back("/controls/flight/elevator");
    variables["/controls/flight/elevator"] = 21;
    insertOrder.push_back("/controls/flight/rudder");
    variables["/controls/flight/rudder"] = 22;
    insertOrder.push_back("/controls/flight/flaps");
    variables["/controls/flight/flaps"] = 23;
    insertOrder.push_back("/controls/engines/engine/throttle");
    variables["/controls/engines/engine/throttle"] = 24;
    insertOrder.push_back("/controls/engines/current-engine/throttle");
    variables["/controls/engines/current-engine/throttle"] = 25;
    insertOrder.push_back("/controls/switches/master-avionics");
    variables["/controls/switches/master-avionics"] = 26;
    insertOrder.push_back("/controls/switches/starter");
    variables["/controls/switches/starter"] = 27;
    insertOrder.push_back("/engines/active-engine/auto-start");
    variables["/engines/active-engine/auto-start"] = 28;
    insertOrder.push_back("/controls/flight/speedbrake");
    variables["/controls/flight/speedbrake"] = 29;
    insertOrder.push_back("/sim/model/c172p/brake-parking");
    variables["/sim/model/c172p/brake-parking"] = 30;
    insertOrder.push_back("/controls/engines/engine/primer");
    variables["/controls/engines/engine/primer"] = 31;
    insertOrder.push_back("/controls/engines/current-engine/mixture");
    variables["/controls/engines/current-engine/mixture"] = 32;
    insertOrder.push_back("/controls/switches/master-bat");
    variables["/controls/switches/master-bat"] = 33;
    insertOrder.push_back("/controls/switches/master-alt");
    variables["/controls/switches/master-alt"] = 34;
    insertOrder.push_back("/engines/engine/rpm");
    variables["/engines/engine/rpm"] = 35;

    //here we create a socket.
    //1-

    if (socketSC == -1) {
        cerr << "Couldn't create socket!" << endl;
        exit(1);
    }

    //2-
    sockaddr_in address, clin;
    address.sin_family = AF_INET;
    //use any to specify ip address
    address.sin_addr.s_addr = INADDR_ANY;

    //here the port will be the port we are given, we check if its an expression or not.
    string port = array[index + 1];
    port.pop_back();
    if (isnt_number(port)) {
        auto* i = new Interpreter();
        Expression *e = nullptr;
        e = i->interpret(port);
        double val = e->calculate();
        int x = round(val);
        address.sin_port = htons(x);
    } else {
      //  cout <<port << endl;
        address.sin_port = htons(stoi(port));
    }

    //try to bind the socket to an ip address.
    if (bind(socketSC, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Couldn't bind the socket" << endl;
        exit(1);
    }

    //3-
    //listening to connections.
    listen(socketSC, 5);
    //char buffer[1024] = {0};

    int cl = sizeof(clin);
    int newSC = accept(socketSC, (struct sockaddr *) &clin, (socklen_t *) &cl);
    newS = newSC;
    if (newSC < 0) {
        cout << "Error" << endl;
    } else {
        cout << "Connected" << endl;
    }
    //we keep this loop running to keep getting values.
    while (true) {
        char buffer[1024] = {0};
        int valread = read(newSC, buffer, 1024);
        if (valread < 0) {
            cerr << "Error reading from the client" << endl;
            closeSocketServer();
            exit(1);
        }
        run(buffer);
        loop = true;
    }
}
