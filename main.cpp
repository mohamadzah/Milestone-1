#include <iostream>
#include "lexer.h"
#include "SymbolTable.h"
#include "Parser.h"
#include "ConnectCommand.h"

int main(int argc, char *argv[]) {
    //read file from argument
    string filename = argv[1];
    ifstream readFile;
    //open file
    readFile.open(filename, ios::in);
    //opening the file, and sending it to the lexer function to sort the commands.
    if (readFile.is_open()) {
        vector<string> arr = lexerCommands(readFile);
        auto * table = new SymbolTable(arr);
        table->setMapKeys();
        auto * parser = new Parser(table);
        parser->setMap();
        parser->parser();
        //close file.
        readFile.close();
        //close sockets
        closeSocket();
        closeSocketServer();
    } else {
        cout << "Couldn't open file" << endl;
    }
    return 0;
}
