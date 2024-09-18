#include <iostream>

#include "PotentialField.h"

enum command { eCreate, ePoint, eMove, eClear, eUpdate, eExit };
command hashit(std::string c) {
    if (c == "CREATE") return eCreate;
    if (c == "POINT") return ePoint;
    if (c == "MOVE") return eMove;
    if (c == "CLEAR") return eClear;
    if (c == "UPDATE") return eUpdate;
    if (c == "EXIT") return eExit;
}

int main() {
    // string to store commands
    std::string command;
    std::getline(std::cin, command);

    while (command != "EXIT") {
        switch (hashit(command))
        case eCreate:
            // get dimensions

            // get next command
            std::getline(std::cin, command);
    }

    return 0;
}