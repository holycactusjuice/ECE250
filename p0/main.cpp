#include <iostream>

#include "PotentialField.h"

enum command { eCreate, ePoint, eMove, eClear, eUpdate, eExit };
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

                pf.addPoint(type, x, y);
            } break;

            case eMove: {
                // get inputs
                int x, y;
                std::cin >> x;
                std::cin >> y;

                pf.move(x, y);
            } break;

            case eClear: {
                pf.clear();
            } break;

            case eUpdate: {
                // get inputs
                double newK;
                std::cin >> newK;

                pf.updateK(newK);
            } break;
        }

        // get next command
        std::cin >> command;
    }

    return 0;
}