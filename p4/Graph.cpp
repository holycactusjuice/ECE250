#include "Graph.h"

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "IllegalException.h"
#include "Node.h"
#include "PriorityQueue.h"

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

        if (type == "relationships") {
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
        } else if (type == "entities") {
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
    // validate inputs
    try {
        validateInput(id1);
        validateInput(id2);
    } catch (IllegalException &e) {
        return "illegal argument";
    }

    // we will use Dijkstra's algorithm to find the path

    // find node with id1
    Node *sourceNode = findNode(id1);
    // find node with id2
    Node *destinationNode = findNode(id2);

    // if source or destination not found, return failure
    if (sourceNode == nullptr || destinationNode == nullptr) {
        return "failure";
    }

    // set all nodes to unvisited and distance to infinity
    for (Node &node : nodes) {
        node.setQueued(false);
        node.setDistance(INT_MIN);
    }

    // set source node distance to 0
    sourceNode->setDistance(0);

    PriorityQueue pq;

    // insert source node into priority queue
    pq.push(sourceNode);
    sourceNode->setQueued(true);

    pq.print();

    // bool to check if destination node is reached
    bool reached = false;

    // loop until priority queue is empty
    while (!pq.empty()) {
        // get node with greatest distance
        Node *currentNode = pq.extractMax();
        std::cout << "extracted " << currentNode->getId() << std::endl;
        pq.print();

        // if current node is destination, break
        if (currentNode->getId() == destinationNode->getId()) {
            reached = true;
            break;
        }

        // relax edges
        for (const auto &relationship : currentNode->getRelationships()) {
            // get neighbour node
            Node *neighbourNode = std::get<0>(relationship);
            // get edge weight
            double edgeWeight = std::get<2>(relationship);
            // calculate potential new distance
            double newDistance = currentNode->getDistance() + edgeWeight;
            // if new distance is GREATER than neighbour node's distance, update
            if (newDistance > neighbourNode->getDistance()) {
                neighbourNode->setDistance(newDistance);
                std::cout << "making " << currentNode->getId() << " parent of "
                          << neighbourNode->getId() << std::endl;
                // update parent if current node is not visited
                if (!neighbourNode->getQueued()) {
                    neighbourNode->setParent(currentNode);
                }
                // update priority queue
                pq.heapifyUp(pq.size() - 1);
            }
            // if neighbour node is not in priority queue, insert
            if (!neighbourNode->getQueued()) {
                std::cout << "pushing " << neighbourNode->getId() << std::endl;
                pq.push(neighbourNode);
                neighbourNode->setQueued(true);
                pq.print();
            }
        }
    }

    // if destination node is not reached, return failure
    if (!reached) {
        return "failure";
    }

    sourceNode->setParent(nullptr);

    // get path from destination to source
    std::vector<std::string> path;

    Node *currentNode = destinationNode;

    while (currentNode != nullptr) {
        path.push_back(currentNode->getId());
        std::cout << "adding " << currentNode->getId() << std::endl;
        currentNode = currentNode->getParent();
    }

    // reverse path
    std::string result = "";

    for (int i = path.size() - 1; i >= 0; i--) {
        result += path[i] + " ";
    }

    // add total distance
    result += std::to_string(destinationNode->getDistance());

    return result;
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