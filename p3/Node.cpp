#include "Node.h"

#include <algorithm>
#include <iostream>
#include <vector>

Node::Node() : label("") {}

Node::~Node() {
    for (Node* child : children) delete child;
    children.clear();
}

// getter and setter methods for the children
const std::vector<Node*>& Node::getChildren() const { return children; }

void Node::addChild(Node* child) { children.push_back(child); }

void Node::removeChild(int index) {
    if (index >= 0 && index < children.size()) {
        delete children[index];
        children.erase(children.begin() + index);
    }
}

// getter and setter methods for the label
std::string Node::getLabel() const { return label; }

void Node::setLabel(std::string value) { label = value; }

// method to check if the node is terminal
bool Node::isTerminal() const {
    // node is terminal if it has no children
    return children.empty();
}