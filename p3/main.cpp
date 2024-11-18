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

    // instantiate PotentialField object
    OpenAddressingHashTable oaht;
    SeparateChainingHashTable scht;

    HashTable* ht;

    // keep program running until EXIT is reached
    while (hashit(command) != eExit) {
        switch (hashit(command)) {
            case eNew: {
                int size;
                int hashType;
                std::cin >> size;
                std::cin >> hashType;

                if (hashType == 0) {
                    ht = &oaht;
                } else {
                    ht = &scht;
                }

                std::string result = ht->newTable(size);
                std::cout << result << std::endl;

                break;
            }
            case eStore: {
                int id;
                std::string charstring;
                std::cin >> id;

                // clear the newline and get the rest of the string
                std::cin.ignore();

                std::getline(std::cin, charstring);

                std::string result = ht->store(id, charstring);
                std::cout << result << std::endl;

                break;
            }
            case eSearch: {
                int id;
                std::cin >> id;

                std::string result = ht->search(id);
                std::cout << result << std::endl;

                break;
            }
            case eDelete: {
                int id;
                std::cin >> id;

                std::string result = ht->deleteKey(id);
                std::cout << result << std::endl;

                break;
            }
            case eCorrupt: {
                int id;
                std::string charstring;
                std::cin >> id;

                // clear the newline and get the rest of the string
                std::cin.ignore();

                std::getline(std::cin, charstring);

                std::string result = ht->corrupt(id, charstring);
                std::cout << result << std::endl;

                break;
            }
            case eValidate: {
                int id;
                std::cin >> id;

                std::string result = ht->validate(id);
                std::cout << result << std::endl;

                break;
            }
            case ePrint: {
                int i;
                std::cin >> i;

                std::string result = ht->print(i);
                std::cout << result << std::endl;

                break;
            }
        }

        // get next command
        std::cin >> command;
    }

    return 0;
}