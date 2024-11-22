#include "Node.h"

#include <string>
#include <tuple>
#include <vector>

Node::Node(std::string id, std::string name, std::string type)
    : id(id), name(name), type(type) {}

std::string Node::getId() { return this->id; }

std::string Node::getName() { return this->name; }

std::string Node::getType() { return this->type; }

void Node::setName(std::string name) { this->name = name; }

void Node::setType(std::string type) { this->type = type; }

std::vector<std::tuple<std::string, std::string, double>>
Node::getRelationships() {
    return this->relationships;
}

void Node::addRelationship(std::string destinationId, std::string label,
                           double weight) {
    bool exists = false;
    // check if relationship with destination already exists
    for (std::tuple<std::string, std::string, double> &relationship :
         this->relationships) {
        // if destination id found, return
        if (std::get<0>(relationship) == destinationId) {
            std::get<1>(relationship) = label;
            std::get<2>(relationship) = weight;
            exists = true;
        }
    }
    if (!exists) {
        this->relationships.push_back(
            std::make_tuple(destinationId, label, weight));
    }
}

void Node::removeRelationship(std::string destinationId) {}