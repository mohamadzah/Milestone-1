//
// Created by user on 12/21/2019.
//

#include "ConditionParser.h"

#define SMLR "<,"
#define GRTR ">,"
#define SEQUAL "<=,"
#define GEQUAL ">=,"
#define EQUAL "==,"
#define NOTEQUAL "!=,"

/**
 * ConditionParser.cpp file.
 *
 * Here we implement the execute function which is responsible for executing a while or if command,
 * we create the two operands, and the conditional operator and create a condition for the loop/if
 * We create a hashmap that includes the commands that are created in between the brackets, and we
 * will keep executing those commands within the loop, or execute them once if we have a if condition
 *
 */

int ConditionParser::execute(vector<string> array, int index) {
    DefineVarCommand *v = new DefineVarCommand();
    map<string, string> mapC = v->returnMap();
    int s = 0;
    string biOp, c1, c2, type = array[index];
    bool condition;
    int i = index;
    i++;
    // create a string that contains the first operand
    while (array[i] != SMLR && array[i] != GRTR && array[i] != SEQUAL
           && array[i] != GEQUAL && array[i] != EQUAL && array[i] != NOTEQUAL) {
        c1 += array[i];
        c1.pop_back();
        i++;
    }
    //we have the first part of the condition.
    i++;
    //create the second operand
    while (array[i] != "{,") {
        c2 += array[i];
        c2.pop_back();
        i++;
    }
    double bool1;
    double bool2;
    //we have the two operands , we have to check each one what it means.
    //initialize bool1, we will check all the options of what it might be.
    if (mapC.find(c1) != mapC.end()) {
        auto k = mapC.find(c1)->second;
        bool1 = SymbolTable::getValue(k);
        //else if it is an expression
    } else if (isnt_number(c1)) {
        auto *itp = new Interpreter();
        Expression *e = nullptr;
        e = itp->interpret(c1);
        bool1 = e->calculate();
    } else {
        //if not a symbol and not an expression we check for letters.
        int k = 0;
        while (k < c1.length()) {
            if (isalpha(c1[k])) {
                //also not a number, not expression, not symbol = invalid condition, throw cerr
                cerr << "Error, invalid operand" << endl;
                exit(1);
            }
            k++;
        }
        bool1 = stod(c1);
    }
    //if we reached here that means we have a bool1 ready, we will do the same to the second operand.
    if (mapC.find(c2) != mapC.end()) {
        auto k = mapC.find(c2)->second;
        bool2 = SymbolTable::getValue(k);
        //else if it is an expression
    } else if (isnt_number(c2)) {
        auto *itp = new Interpreter();
        Expression *e = nullptr;
        e = itp->interpret(c2);
        bool2 = e->calculate();
    } else {
        //if not a symbol and not an expression we check for letters.
        int k = 0;
        while (k < c2.length()) {
            if (isalpha(c2[k])) {
                //also not a number, not expression, not symbol = invalid condition, throw cerr
                cerr << "Error, invalid operand" << endl;
                exit(1);
            }
            k++;
        }
        bool2 = stod(c2);
    }
    //bool1, bool2 ready, now we create will create the condition structure.
    i++;
    int flag = 0;
    if (array[i - 3] == SMLR) {
        condition = bool1 < bool2;
        flag = 1;
    } else if (array[i - 3] == GRTR) {
        condition = bool1 > bool2;
        flag = 1;
    } else if (array[i - 3] == SEQUAL) {
        condition = bool1 <= bool2;
        flag = 1;
    } else if (array[i - 3] == GEQUAL) {
        condition = bool1 >= bool2;
        flag = 1;
    } else if (array[i - 3] == EQUAL) {
        condition = bool1 == bool2;
        flag = 1;
    } else if (array[i - 3] == NOTEQUAL) {
        condition = bool1 != bool2;
        flag = 1;
    }
    //check if we had a valid conditional operator
    if (flag == 0) {
        cerr << "Invalid conditional operator" << endl;
        exit(1);
    }
    string command;
    s = i;
    map<string, class Command *> hashMap;
    while (array[i] != "},") {
        /*in this loop, we will create a mini parser, in other words i will create a map of commands, and the commands
         * that we create will be executed either in a while loop or an if condition.   */
        command = array[i];
        command.pop_back();
        if (command == "var") {
            hashMap.insert({command, new DefineVarCommand});
        } else if (SymbolTable::getKey(command)) {
            hashMap.insert({command, new SetVarCommand});
        } else if (command == "Sleep") {
            hashMap.insert({command, new SleepCommand});
        } else if (command == "if" || command == "while") {
            hashMap.insert({command, new ConditionParser});
        } else if (command == "Print") {
            hashMap.insert({command, new PrintCommand});
        }
        i++;
    }

    //now we have the condition ready, and the Hashmap ready, we are ready to execute.
    //in order to not to write the code twice, we will create a while no matter whether we have a if or a while
    //but inside the while, after the first execution of the commands,
    // we will check whether we have an if condition or not, if we do we will break the while loop because we had a if condition.
    while (condition) {
        //now we have a map full of commands, now we execute them.
        //if the operand is a variable, we will keep checking symboltable in order to update it.
        if (mapC.find(c1) != mapC.end()) {
            auto k = mapC.find(c1)->second;
            bool1 = SymbolTable::getValue(k);
        }
        if (mapC.find(c2) != mapC.end()) {
            auto k = mapC.find(c1)->second;
            bool2 = SymbolTable::getValue(k);
        }
        //keep checking the condition and updating it.
        if (array[s - 3] == SMLR) {
            condition = bool1 < bool2;
        } else if (array[s - 3] == GRTR) {
            condition = bool1 > bool2;
        } else if (array[s - 3] == SEQUAL) {
            condition = bool1 <= bool2;
        } else if (array[s - 3] == GEQUAL) {
            condition = bool1 >= bool2;
        } else if (array[s - 3] == EQUAL) {
            condition = bool1 == bool2;
        } else if (array[s - 3] == NOTEQUAL) {
            condition = bool1 != bool2;
        }
        string pop;
        // execute if the condition is satisfied.
        if (condition) {
            int ind = s;
            while (array[ind] != "},") {
                pop = array[ind];
                pop.pop_back();
                if (hashMap.find(pop) != hashMap.end()) {
                    Command *c = hashMap.find(pop)->second;
                    ind += c->execute(array, ind);
                }
            }
        }
        //if it is an if condition, we will break the loop and exit.
        if (type == "if,") {
            break;
        }
    }
    return i-index+1;
}

ConditionParser::ConditionParser() = default;
