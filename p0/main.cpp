#include "PotentialField.h"

#include <iostream>

// enum to allow switch case using input strings
enum command { eCreate, ePoint, eMove, eClear, eUpdate, eExit };
// converts input command strings to command type
command hashit(std::string c) {
    if (c == "CREATE") return eCreate;
    if (c == "POINT") return ePoint;
    if (c == "MOVE") return eMove;
    if (c == "CLEAR") return eClear;
    if (c == "UPDATE") return eUpdate;
    return eExit;
}

int main() {
    // string to store commands
    std::string command;
    std::cin >> command;

    // instantiate PotentialField object
    PotentialField pf;

    // keep program running until EXIT is reached
    while (hashit(command) != eExit) {
        switch (hashit(command)) {
            case eCreate: {
                // get inputs
                int w, h;
                std::cin >> w;
                std::cin >> h;
                // create the grid
                pf.create(w, h);
            } break;

            case ePoint: {
                // get inputs
                char type;
                int x, y;
                std::cin >> type;
                std::cin >> x;
                std::cin >> y;
                // add point
                pf.point(type, x, y);
            } break;

            case eMove: {
                // get inputs
                int x, y;
                std::cin >> x;
                std::cin >> y;
                // print potential
                pf.move(x, y);
            } break;

            case eClear: {
                // clear grid
                pf.clear();
            } break;

            case eUpdate: {
                // get inputs
                double newK;
                std::cin >> newK;
                // update value of K
                pf.update(newK);
            } break;
        }

        // get next command
        std::cin >> command;
    }

    return 0;
}