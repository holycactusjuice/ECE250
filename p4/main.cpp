#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Graph.h"
#include "Node.h"

// enum to allow switch case using input strings
enum command {
    eLoad,
    eRelationship,
    eEntity,
    ePrint,
    eDelete,
    ePath,
    eHighest,
    eFindAll,
    eExit
};
// converts input command strings to command type
command hashit(std::string c) {
    if (c == "LOAD") return eLoad;
    if (c == "RELATIONSHIP") return eRelationship;
    if (c == "ENTITY") return eEntity;
    if (c == "PRINT") return ePrint;
    if (c == "DELETE") return eDelete;
    if (c == "PATH") return ePath;
    if (c == "HIGHEST") return eHighest;
    if (c == "FINDALL") return eFindAll;
    return eExit;
}

int main() {
    // string to store commands
    std::string command;
    std::cin >> command;

    Graph* g = new Graph();

    // keep program running until EXIT is reached
    while (hashit(command) != eExit) {
        std::string result;
        switch (hashit(command)) {
            case eLoad: {
                std::string filename;
                std::string type;
                std::cin >> filename;
                std::cin >> type;

                result = g->load(filename, type);

                break;
            }
            case eRelationship: {
                std::string sourceId;
                std::string label;
                std::string destinationId;
                double weight;
                std::cin >> sourceId;
                std::cin >> label;
                std::cin >> destinationId;
                std::cin >> weight;

                result =
                    g->relationship(sourceId, label, destinationId, weight);

                break;
            }
            case eEntity: {
                std::string id;
                std::string name;
                std::string type;
                std::cin >> id;
                std::cin >> name;
                std::cin >> type;

                result = g->entity(id, name, type);

                break;
            }
            case ePrint: {
                std::string id;
                std::cin >> id;

                result = g->print(id);

                break;
            }
            case eDelete: {
                std::string id;
                std::cin >> id;

                result = g->deleteNode(id);

                break;
            }
            case ePath: {
                std::string id1;
                std::string id2;
                std::cin >> id1;
                std::cin >> id2;

                result = g->path(id1, id2);

                break;
            }
            case eHighest: {
                result = g->highest();

                break;
            }
            case eFindAll: {
                std::string fieldType;
                std::string fieldString;
                std::cin >> fieldType;
                std::cin >> fieldString;

                result = g->findAll(fieldType, fieldString);

                break;
            }
            default:
                break;
        }
        std::cout << result << std::endl;

        // get next command
        std::cin >> command;
    }

    return 0;
}