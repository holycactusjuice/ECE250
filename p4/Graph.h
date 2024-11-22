#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <tuple>
#include <vector>

#include "Node.h"

class Graph {
   private:
    std::vector<Node> nodes;

    void validateInput(std::string input);

   public:
    Graph();
    std::string load(std::string filename, std::string type);
    std::string relationship(std::string sourceId, std::string label,
                             std::string destinationId, double weight);
    std::string entity(std::string id, std::string name, std::string type);
    std::string print(std::string id);
    std::string deleteNode(std::string id);
    std::string path(std::string id1, std::string id2);
    std::string highest();
    std::string findAll(std::string fieldType, std::string fieldString);
};

#endif