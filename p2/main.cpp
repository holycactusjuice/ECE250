#include <iostream>

#include "hashtable.h"

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
    HashTable ht;

    // keep program running until EXIT is reached
    while (hashit(command) != eExit) {
        switch (hashit(command)) {
            case eNew: {
                int size;
                int hashType;
                std::cin >> size;
                std::cin >> hashType;
                ht.newTable(size, hashType);
                break;
            }
            case eStore: {
                int id;
                std::string charstring;
                std::cin >> id;
                std::cin >> charstring;
                ht.store(id, charstring);
                break;
            }
            case eSearch: {
                int id;
                std::cin >> id;
                ht.search(id);
                break;
            }
            case eDelete: {
                int id;
                std::cin >> id;
                ht.deleteKey(id);
                break;
            }
            case eCorrupt: {
                int id;
                std::string charstring;
                std::cin >> id;
                std::cin >> charstring;
                ht.corrupt(id, charstring);
                break;
            }
            case eValidate: {
                int id;
                std::cin >> id;
                ht.validate(id);
                break;
            }
            case ePrint: {
                int i;
                std::cin >> i;
                ht.print(i);
                break;
            }
        }

        // get next command
        std::cin >> command;
    }

    return 0;
}