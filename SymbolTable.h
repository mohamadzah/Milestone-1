//
// Created by user on 12/19/2019.
//

#ifndef FLIGHTGEAR_SYMBOLTABLE_H
#define FLIGHTGEAR_SYMBOLTABLE_H

#include <map>
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

class SymbolTable {
public:
    //keys vector is where we store the name of all variables in the lexical analysed vector.
    static vector<string> keys;
    // vector that contains the tokens from the file.
    vector<string> array;
    //a symTable that connects the variable, with its line and its value.
    static map<string, pair<string,double>> symTable;
public:
    //map to initialize keys and symTable.
    void setMapKeys();
public:
    //constructors.
    explicit SymbolTable(vector<string> _array);
    SymbolTable();
    //access to  value in O(1)
    static double getValue(string key);
    vector<string> getArray();
    map<string, pair<string,double>> getTable();
    //check if key exists.
    static bool getKey(string key);
    //add new line , key , value
    static void addNewKey(string key,string line, double value);
    static bool getV(string key);
};

#endif //FLIGHTGEAR_SYMBOLTABLE_H
