#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Node.h"
#include "Trie.h"
#include "ece250_socket.h"

// enum to allow switch case using input strings
enum command {
    eLoad,
    eInsert,
    eClassify,
    eErase,
    ePrint,
    eEmpty,
    eClear,
    eSize,
    eExit
};
// converts input command strings to command type
command hashit(std::string c) {
    if (c == "LOAD") return eLoad;
    if (c == "INSERT") return eInsert;
    if (c == "CLASSIFY") return eClassify;
    if (c == "ERASE") return eErase;
    if (c == "PRINT") return ePrint;
    if (c == "EMPTY") return eEmpty;
    if (c == "CLEAR") return eClear;
    if (c == "SIZE") return eSize;
    return eExit;
}

int main() {
    // string to store commands
    std::string command;
    std::cin >> command;

    Trie* t = new Trie();

    // keep program running until EXIT is reached
    while (hashit(command) != eExit) {
        std::string result;
        switch (hashit(command)) {
            case eLoad: {
                std::string filename;
                std::cin >> filename;

                result = t->load(filename);

                break;
            }
            case eInsert: {
                std::string classification;
                std::cin.ignore();
                std::getline(std::cin, classification);
                result = t->insert(classification);

                break;
            }
            case eClassify: {
                std::string input;
                std::cin.ignore();
                std::getline(std::cin, input);

                result = t->classify(input);

                break;
            }
            case eErase: {
                std::string classification;
                std::cin.ignore();
                std::getline(std::cin, classification);

                result = t->erase(classification);

                break;
            }
            case ePrint: {
                result = t->print();

                break;
            }
            case eEmpty: {
                result = t->empty();

                break;
            }
            case eClear: {
                result = t->clear();

                break;
            }
            case eSize: {
                result = t->size();

                break;
            }
        }
        std::cout << result << std::endl;

        // get next command
        std::cin >> command;
    }

    return 0;
}