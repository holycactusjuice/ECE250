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
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
              (c >= '0' && c <= '9')))
            throw IllegalException();
    }
}

Node *Graph::findNode(std::string id) {
    // find node with id
    auto it = std::find_if(nodes.begin(), nodes.end(),
                           [&id](Node &node) { return node.getId() == id; });

    // if node not found, return nullptr
    if (it == nodes.end()) {
        return nullptr;
    }

    return &(*it);
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
    sourceNode->addRelationship(destinationNode, label, weight);
    destinationNode->addRelationship(sourceNode, label, weight);

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
    Node *targetNode = findNode(id);

    // if node not found, return failure
    if (targetNode == nullptr) {
        return "failure";
    }

    // get relationships of node
    auto relationships = targetNode->getRelationships();

    // print relationships
    std::string result = "";
    for (const auto &relationship : relationships) {
        // add id to result
        result += std::get<0>(relationship)->getId() + " ";
    }
    // remove trailing space
    if (!result.empty()) {
        result.pop_back();
    }

    return result;
}

std::string Graph::deleteNode(std::string id) {
    try {
        validateInput(id);
    } catch (IllegalException &e) {
        return "illegal argument";
    }

    // find node with id
    Node *targetNode = findNode(id);

    // if node not found, return failure
    if (targetNode == nullptr) {
        return "failure";
    }

    // get relationships of node
    auto relationships = targetNode->getRelationships();

    // we need to remove this node from all its neighbours' relationships vector
    for (const auto &relationship : relationships) {
        // get the neighbour node id of this relationship
        Node *neighbourNode = std::get<0>(relationship);
        // remove this node from the neighbour's relationships vector
        neighbourNode->removeRelationship(id);
    }

    // remove node
    nodes.erase(
        std::remove_if(nodes.begin(), nodes.end(),
                       [&id](Node &node) { return node.getId() == id; }),
        nodes.end());

    return "success";
}

std::string Graph::path(std::string id1, std::string id2) {
    try {
        validateInput(id1);
        validateInput(id2);
    } catch (IllegalException &e) {
        return "illegal argument";
    }

    return "success";
}

std::string Graph::findAll(std::string fieldType, std::string fieldString) {
    try {
        validateInput(fieldType);
        validateInput(fieldString);
    } catch (IllegalException &e) {
        return "illegal argument";
    }

    return "success";
}

std::string Graph::highest() { return "success"; }