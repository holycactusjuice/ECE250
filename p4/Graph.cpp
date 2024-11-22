#include "Graph.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "IllegalException.h"
#include "Node.h"

Graph::Graph() : nodes({}) {}

void Graph::validateInput(std::string input) {
    for (char c : input) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9'))
            throw IllegalException();
    }
}

std::string Graph::load(std::string filename, std::string type) {
    // open file
    std::ifstream file(filename);

    // read file line by line
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        if (type == "relationship") {
            // read inputs
            std::string sourceId;
            std::string label;
            std::string destinationId;
            double weight;

            // parse inputs
            iss >> sourceId;
            iss >> label;
            iss >> destinationId;
            iss >> weight;

            // add relationship
            relationship(sourceId, label, destinationId, weight);
        } else if (type == "entity") {
            // read inputs
            std::string id;
            std::string name;
            std::string type;

            // parse inputs
            iss >> id;
            iss >> name;
            iss >> type;

            // add relationship
            entity(id, name, type);
        }
    }

    // close file
    file.close();

    return "success";
}

std::string Graph::relationship(std::string sourceId, std::string label,
                                std::string destinationId, double weight) {
    // instantiate nodes for source and destination
    Node *sourceNode = nullptr;
    Node *destinationNode = nullptr;
    // loop through nodes to find source and destination
    for (Node &node : nodes) {
        if (node.getId() == sourceId) {
            sourceNode = &node;
        } else if (node.getId() == destinationId) {
            destinationNode = &node;
        }
    }

    // if source or destination not found, return failure
    if (sourceNode == nullptr || destinationNode == nullptr) {
        return "failure";
    }

    // add relationship to both source and destination
    // addRelationship updates relationship if it already exists
    sourceNode->addRelationship(destinationId, label, weight);
    destinationNode->addRelationship(sourceId, label, weight);

    return "success";
}

std::string Graph::entity(std::string id, std::string name, std::string type) {
    bool exists = false;
    // check if node already exists
    for (Node &node : nodes) {
        if (node.getId() == id) {
            node.setName(name);
            node.setType(type);
            exists = true;
        }
    }

    // add node
    if (!exists) {
        nodes.push_back(Node(id, name, type));
    }

    return "success";
}

std::string Graph::print(std::string id) {
    try {
        validateInput(id);
    } catch (IllegalException &e) {
        return "illegal argument";
    }
    // find node with id
    auto it = std::find_if(nodes.begin(), nodes.end(),
                           [&id](Node &node) { return node.getId() == id; });

    // if node not found, return failure
    if (it == nodes.end()) {
        return "failure";
    }

    // get relationships of node
    auto relationships = it->getRelationships();

    // print relationships
    std::string result = "";
    for (const auto &relationship : relationships) {
        // add id to result
        result += std::get<0>(relationship) + " ";
    }
    // remove trailing space
    if (!result.empty()) {
        result.pop_back();
    }
    // add newline
    result += "\n";

    return result;
}

std::string Graph::deleteNode(std::string id) {
    try {
        validateInput(id);
    } catch (IllegalException &e) {
        return "illegal argument";
    }

    // find node with id
    auto it = std::find_if(nodes.begin(), nodes.end(),
                           [&id](Node &node) { return node.getId() == id; });

    // if node not found, return failure
    if (it == nodes.end()) {
        return "failure";
    }

    // get relationships of node
    auto relationships = it->getRelationships();
}
