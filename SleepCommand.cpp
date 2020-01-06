//
// Created by mohamad on 26/12/2019.
//

#include "SleepCommand.h"
#include "SetVarCommand.h"
#include "Interpreter.h"
#include <cmath>

// create a function that will make the main thread sleep
int SleepCommand::execute(vector<string> array, int index) {
    //we get the duration of the sleep command.
    string time = array[index+1];
    time.pop_back();
    // we need to check if we have an expression or a number.
    if (isnt_number(time)) {
        auto *i = new Interpreter();
        Expression *e = nullptr;
        e = i->interpret(time);
        double val = e->calculate();
        int x = round(val);
        this_thread::sleep_for(std::chrono::milliseconds(x));
    } else {
        auto i = 0;
        while (i < time.length()) {
            if (isalpha(time[i])) {
                cerr << "Can't execute command! invalid value" << endl;
                exit(2);
            }
            i++;
         }
        // if not an expression, its a normal decimal value, so we convert string and call sleep for main thread
        this_thread::sleep_for(std::chrono::milliseconds(stoi(time)));
    }
    return 2;
}

SleepCommand::SleepCommand() {}
