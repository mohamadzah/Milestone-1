//
// Created by user on 12/19/2019.
//

#include "SymbolTable.h"
#include <sstream>
#include <utility>
#include <bits/stdc++.h>

map<string, pair<string,double>> SymbolTable::symTable;

vector<string> SymbolTable::keys;
//return value of a variable using its path.
double SymbolTable::getValue(string key) {
    if (symTable.find(key) != symTable.end()) {
        return  symTable.find(key)->second.second;
    } else {
        return 0;
    }
}
/**
 * SetMapKeys
 *
 * In this function we initialize the symTable with temporary values, we add all the possible
 * paths according to the xml file we were provided.
 *
 * then we will create a vector that is filled with every variable that is created in the file.
 * so we can distinguish in the process of creating commands, which token is what.
 *
 * then we will update the variable name for each path that is used.
 *
 */
void SymbolTable::setMapKeys() {
    symTable["/instrumentation/airspeed-indicator/indicated-speed-kt"] = {"not set", 0};
    symTable["/sim/time/warp"] = {"not set", 0};
    symTable["/controls/switches/magnetos"] = {"not set", 0};
    symTable["/instrumentation/heading-indicator/offset-deg"] = {"not set", 0};
    symTable["/instrumentation/altimeter/indicated-altitude-ft"] = {"not set", 0};
    symTable["/instrumentation/altimeter/pressure-alt-ft"] = {"not set", 0};
    symTable["/instrumentation/attitude-indicator/indicated-pitch-deg"] = {"not set", 0};
    symTable["/instrumentation/attitude-indicator/indicated-roll-deg"] = {"not set", 0};
    symTable["/instrumentation/attitude-indicator/internal-pitch-deg"] = {"not set", 0};
    symTable["/instrumentation/attitude-indicator/internal-roll-deg"] = {"not set", 0};
    symTable["/instrumentation/encoder/indicated-altitude-ft"] = {"not set", 0};
    symTable["/instrumentation/encoder/pressure-alt-ft"] = {"not set", 0};
    symTable["/instrumentation/gps/indicated-altitude-ft"] = {"not set", 0};
    symTable["/instrumentation/gps/indicated-ground-speed-kt"] = {"not set", 0};
    symTable["/instrumentation/gps/indicated-vertical-speed"] = {"not set", 0};
    symTable["/instrumentation/heading-indicator/indicated-heading-deg"] = {"not set", 0};
    symTable["/instrumentation/magnetic-compass/indicated-heading-deg"] = {"not set", 0};
    symTable["/instrumentation/slip-skid-ball/indicated-slip-skid"] = {"not set", 0};
    symTable["/instrumentation/turn-indicator/indicated-turn-rate"] = {"not set", 0};
    symTable["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = {"not set", 0};
    symTable["/controls/flight/aileron"] = {"not set", 0};
    symTable["/controls/flight/elevator"] = {"not set", 0};
    symTable["/controls/flight/rudder"] = {"not set", 0};
    symTable["/controls/flight/flaps"] = {"not set", 0};
    symTable["/controls/engines/engine/throttle"] = {"not set", 0};
    symTable["/controls/engines/current-engine/throttle"] = {"not set", 0};
    symTable["/controls/switches/master-avionics"] = {"not set", 0};
    symTable["/controls/switches/starter"] = {"not set", 0};
    symTable["/engines/active-engine/auto-start"] = {"not set", 0};
    symTable["/controls/flight/speedbrake"] = {"not set", 0};
    symTable["/sim/model/c172p/brake-parking"] = {"not set", 0};
    symTable["/controls/engines/engine/primer"] = {"not set", 0};
    symTable["/controls/engines/current-engine/mixture"] = {"not set", 0};
    symTable["/controls/switches/master-bat"] = {"not set", 0};
    symTable["/controls/switches/master-alt"] = {"not set", 0};
    symTable["/engines/engine/rpm"] = {"not set", 0};
    string key;
    string temp;
    for (size_t i = 0; i < array.size()-1; ++i) {
        if (array[i] == "var,") {
            //push to the variable name to the keys vector
            if (i + 1 < array.size() - 1) {
                key = array[i + 1];
                key.pop_back();
                keys.push_back(key);
            }
            // check the type of the variable if its <- or ->
            if (array[i + 2] == "->,") {
                if (array[i + 3] == "sim,") {
                    string line;
                    string commaRemove;
                    commaRemove = array[i + 4];
                    commaRemove.pop_back();
                    commaRemove.pop_back();
                    commaRemove.erase(0,1);
                    line += commaRemove;
                    addNewKey(key,line, 0);
                }
            } else if (array[i + 2] == "<-,") {
                if (array[i + 3] == "sim,") {
                    string commaRemove;
                    commaRemove = array[i + 4];
                    commaRemove.pop_back();
                    commaRemove.pop_back();
                    commaRemove.erase(0,1);
                    string line;
                    line += commaRemove;
                    addNewKey(key,line, 0);
                }
            }
        }
    }
}

SymbolTable::SymbolTable(vector<string> array1) {
    array = std::move(array1);
}
//constructor
SymbolTable::SymbolTable() {}
// return array
vector<string> SymbolTable::getArray() {
    return array;
}
//check whether a given string is a path or not.
bool SymbolTable::getV(string key) {
    auto it = symTable.find(key);
    return it != symTable.end();
}
//returns whether a given string is a key or not
bool SymbolTable::getKey(string key) {
    auto it = find(keys.begin(), keys.end(), key);
    return it != keys.end();
}

map<string, pair<string,double>> SymbolTable::getTable() {
    return symTable;
}
// Add a new key or just update the value if it already exists.
void SymbolTable::addNewKey(string name,string line ,double value) {
    if (symTable.find(line) == symTable.end()) {
        symTable.insert({line, {name,value}});
    } else {
        symTable[line] = {name,value};
    }
}

