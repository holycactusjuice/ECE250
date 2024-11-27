#include "Node.h"

#include <algorithm>
#include <climits>
#include <string>
#include <tuple>
#include <vector>

Node::Node(std::string id, std::string name, std::string type)
    : id(id),
      name(name),
      type(type),
      queued(false),
      distance(INT_MIN),
      parent(nullptr) {}

std::string Node::getId() { return this->id; }

std::string Node::getName() { return this->name; }

std::string Node::getType() { return this->type; }

void Node::setName(std::string name) { this->name = name; }

void Node::setType(std::string type) { this->type = type; }

bool Node::getQueued() { return this->queued; }

void Node::setQueued(bool queued) { this->queued = queued; }

bool Node::getProcessed() { return this->processed; }

void Node::setProcessed(bool processed) { this->processed = processed; }

double Node::getDistance() { return this->distance; }

void Node::setDistance(double distance) { this->distance = distance; }

Node *Node::getParent() { return this->parent; }

void Node::setParent(Node *parent) { this->parent = parent; }

std::vector<std::tuple<Node *, std::string, double>> Node::getRelationships() {
    return this->relationships;
}

bool Node::relationshipExists(std::string destinationId) {
    // check if relationship with destination already exists
    for (std::tuple<Node *, std::string, double> &relationship :
         this->relationships) {
        // if destination id found, return true
        if (std::get<0>(relationship)->getId() == destinationId) {
            return true;
        }
    }
    return false;
}

void Node::addRelationship(Node *destinationNode, std::string label,
                           double weight) {
    bool exists = false;
    // check if relationship with destination already exists
    for (std::tuple<Node *, std::string, double> &relationship :
         this->relationships) {
        // if destination id found, return
        if (std::get<0>(relationship)->getId() == destinationNode->getId()) {
            std::get<1>(relationship) = label;
            std::get<2>(relationship) = weight;
            exists = true;
        }
    }
    if (!exists) {
        this->relationships.push_back(
            std::make_tuple(destinationNode, label, weight));
    }
}

void Node::removeRelationship(std::string destinationId) {
    // remove relationship with destination id
    this->relationships.erase(
        std::remove_if(
            // search through relationships vector
            this->relationships.begin(), this->relationships.end(),
            // lambda function with destinationId as input
            [&destinationId](
                std::tuple<Node *, std::string, double> &relationship) {
                // return true if destinationId found
                return std::get<0>(relationship)->getId() == destinationId;
            }),
        this->relationships.end());
}