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
    Node *node = nullptr;

    // find node with id
    for (Node *n : nodes) {
        if (n->getId() == id) {
            node = n;
            break;
        }
    }

    return node;
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
    for (Node *node : nodes) {
        if (node->getId() == sourceId) {
            sourceNode = node;
        } else if (node->getId() == destinationId) {
            destinationNode = node;
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
    for (Node *node : nodes) {
        if (node->getId() == id) {
            node->setName(name);
            node->setType(type);
            exists = true;
        }
    }

    // add node
    if (!exists) {
        nodes.push_back(new Node(id, name, type));
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
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        if ((*it)->getId() == id) {
            delete *it;
            nodes.erase(it);
            break;
        }
    }

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
    for (Node *node : nodes) {
        node->setQueued(false);
        node->setDistance(INT_MIN);
        node->setParent(nullptr);
        node->setProcessed(false);
    }

    // set source node distance to 0
    sourceNode->setDistance(0);

    PriorityQueue pq;

    // insert source node into priority queue
    pq.push(sourceNode);
    sourceNode->setQueued(true);

    // bool to check if destination node is reached
    bool reached = false;

    // loop until priority queue is empty
    while (!pq.empty()) {
        // get node with greatest distance
        Node *currentNode = pq.extractMax();

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
                // update parent if current node is not processed
                // because we don't want to update parent of a node that has
                // already been added to the path
                if (!neighbourNode->getProcessed()) {
                    neighbourNode->setParent(currentNode);
                }
                // update priority queue
                pq.heapifyUp(pq.size() - 1);
            }
            // if neighbour node is not in priority queue, insert
            if (!neighbourNode->getQueued()) {
                pq.push(neighbourNode);
                neighbourNode->setQueued(true);
            }
        }

        currentNode->setProcessed(true);
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

std::string Graph::highest() {
    // we will first use Prim's algorithm to find the max spanning tree
    // then we will run 2 DFSs to find the diameter of the tree

    // set all nodes to unvisited and distance to infinity
    for (Node *node : nodes) {
        node->setQueued(false);
        node->setDistance(INT_MIN);
        node->setParent(nullptr);
        node->setProcessed(false);
    }

    std::vector<Node *> processedNodes;
    std::string result = "";
    double maxDistance = INT_MIN;

    while (processedNodes.size() < nodes.size()) {
        Node *nextNode = nullptr;
        for (Node *node : nodes) {
            if (std::find(processedNodes.begin(), processedNodes.end(), node) ==
                processedNodes.end()) {
                nextNode = node;
                break;
            }
        }

        std::vector<std::tuple<Node *, Node *, double>> maxSpanningTree =
            buildMaxSpanningTree(nextNode);
        if (maxSpanningTree.size() == 0) {
            processedNodes.push_back(nextNode);
            continue;
        }
        // // print max spanning tree
        // for (const auto &edge : maxSpanningTree) {
        //     std::cout << std::get<0>(edge)->getId() << " is connected to "
        //               << std::get<1>(edge)->getId() << " with weight "
        //               << std::get<2>(edge) << std::endl;
        // }

        // start from any node for first dfs
        // we will take the first node in the max spanning tree
        Node *curr = std::get<0>(maxSpanningTree[0]);

        // endpoint will be the node with the greatest distance from start node
        Node *end = curr;

        // set all nodes to unvisited and distance to infinity
        for (Node *node : nodes) {
            node->setQueued(false);
            node->setDistance(INT_MIN);
            node->setParent(nullptr);
            node->setProcessed(false);
        }

        // set start node distance to 0
        curr->setDistance(0);

        // run dfs
        dfs(curr, maxSpanningTree, end, 0);

        // start from endpoint for second dfs
        curr = end;

        // set all nodes to unvisited and distance to infinity

        for (Node *node : nodes) {
            node->setQueued(false);
            node->setDistance(INT_MIN);
            node->setParent(nullptr);
            node->setProcessed(false);
        }

        // set start node distance to 0
        curr->setDistance(0);

        // run dfs
        dfs(curr, maxSpanningTree, end, 0);

        // get path from destination to source

        std::vector<std::string> path;

        Node *currentNode = end;

        while (currentNode != nullptr) {
            // std::cout << currentNode->getId() << " has weight "
            //           << currentNode->getDistance() << std::endl;
            path.push_back(currentNode->getId());
            currentNode = currentNode->getParent();
            processedNodes.push_back(currentNode);
        }

        if (end->getDistance() > maxDistance) {
            maxDistance = end->getDistance();
            // reverse path
            result = "";

            // add start and end nodes
            result += path[path.size() - 1] + " " + path[0] + " ";

            // add total distance
            result += std::to_string(end->getDistance());
        }
    }

    return result == "" ? "failure" : result;
}
std::vector<std::tuple<Node *, Node *, double>> Graph::buildMaxSpanningTree(
    Node *startNode) {
    if (startNode->getRelationships().empty()) {
        return {};
    }

    std::vector<std::tuple<Node *, Node *, double>> maxSpanningTree;

    // start with first node
    startNode->setDistance(0);

    PriorityQueue pq;

    // insert start node into priority queue
    pq.push(startNode);
    startNode->setQueued(true);

    // loop until priority queue is empty
    while (!pq.empty()) {
        // get node with greatest distance
        Node *currentNode = pq.extractMax();

        // if node has already been added to the tree, skip
        if (currentNode->getProcessed()) {
            continue;
        }

        // relax edges
        for (const auto &relationship : currentNode->getRelationships()) {
            // get neighbour node
            Node *neighbourNode = std::get<0>(relationship);
            // get edge weight
            double edgeWeight = std::get<2>(relationship);
            // calculate potential new distance
            double newDistance = edgeWeight;
            // if new distance is GREATER than neighbour node's distance,
            // update
            if (newDistance > neighbourNode->getDistance()) {
                neighbourNode->setDistance(newDistance);
                if (!neighbourNode->getProcessed()) {
                    // add edge to max spanning tree
                    maxSpanningTree.push_back(
                        {currentNode, neighbourNode, edgeWeight});
                }
                // update priority queue
                pq.heapifyUp(pq.size() - 1);
            }
            // if neighbour node is not in priority queue, insert
            if (!neighbourNode->getQueued()) {
                pq.push(neighbourNode);
                neighbourNode->setQueued(true);
            }
        }

        currentNode->setProcessed(true);
    }

    return maxSpanningTree;
}

std::string Graph::findAll(std::string fieldType, std::string fieldString) {
    // find all nodes with fieldString in fieldType

    std::string result = "";

    for (Node *node : nodes) {
        if ((fieldType == "name" && node->getName() == fieldString) ||
            (fieldType == "type" && node->getType() == fieldString)) {
            result += node->getId() + " ";
        }
    }

    // remove trailing space
    if (!result.empty()) {
        result.pop_back();
    }

    return (result.empty()) ? "failure" : result;
}

void Graph::dfs(Node *current,
                const std::vector<std::tuple<Node *, Node *, double>> &tree,
                Node *&maxNode, double currentWeight) {
    current->setProcessed(true);
    current->setDistance(currentWeight);

    if (currentWeight > maxNode->getDistance()) {
        maxNode->setDistance(currentWeight);
        maxNode = current;
    }

    for (const auto &edge : tree) {
        Node *source = std::get<0>(edge);
        Node *dest = std::get<1>(edge);
        double weight = std::get<2>(edge);

        Node *neighbour = (source->getId() == current->getId()) ? dest
                          : (dest->getId() == current->getId()) ? source
                                                                : nullptr;

        if (neighbour && !neighbour->getProcessed()) {
            // update parent
            neighbour->setParent(current);
            dfs(neighbour, tree, maxNode, currentWeight + weight);
        }
    }
}