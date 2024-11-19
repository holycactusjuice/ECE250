#include "Node.h"

#include <algorithm>
#include <iostream>
#include <vector>

// Constructor: Initializes a Node with an empty label.
Node::Node() : label("") {}

// Destructor: Ensures all child nodes are deleted to prevent memory leaks.
Node::~Node() {
    for (Node* child : children) {
        delete child;  // Free memory for each child.
    }
    children.clear();  // Clear the children vector to avoid dangling pointers.
}

// Getter for the children of the node.
const std::vector<Node*>& Node::getChildren() const { return children; }

// Adds a new child to the node.
void Node::addChild(Node* child) {
    if (child) {  // Check for null pointer to avoid undefined behavior.
        children.push_back(child);
    }
}

// Removes a child at the specified index and frees its memory.
void Node::removeChild(int index) {
    if (index >= 0 && index < children.size()) {
        delete children[index];  // Free memory for the child node.
        children.erase(children.begin() +
                       index);  // Remove the pointer from the vector.
    }
}

// Getter for the node's label.
std::string Node::getLabel() const { return label; }

// Setter for the node's label, using move semantics for efficiency.
void Node::setLabel(std::string value) { label = std::move(value); }

// Determines if the node is terminal (i.e., has no children).
bool Node::isTerminal() const { return children.empty(); }
