#include <iostream>
#include <limits>
#include <string>

#include "HashTable.h"
#include "OpenAddressingHashTable.h"
#include "SeparateChainingHashTable.h"

// enum to allow switch case using input strings
enum command {
    eNew,
    eStore,
    eSearch,
    eDelete,
    eCorrupt,
    eValidate,
    ePrint,
    eExit
};
// converts input command strings to command type
command hashit(std::string c) {
    if (c == "NEW") return eNew;
    if (c == "STORE") return eStore;
    if (c == "SEARCH") return eSearch;
    if (c == "DELETE") return eDelete;
    if (c == "CORRUPT") return eCorrupt;
    if (c == "VALIDATE") return eValidate;
    if (c == "PRINT") return ePrint;
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