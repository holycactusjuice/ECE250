#include "Node.h"

#include <algorithm>
#include <iostream>
#include <vector>

class Node {
   private:
    std::vector<Node*> children;  // children of the node
    std::string label;            // label of the node

   public:
    Node();
    ~Node();

    // getter and setter methods for the children
    const std::vector<Node*>& getChildren() const { return children; }
    void addChild(Node* child) {
        children.push_back(child);
    }  // Add a child to the node
    void removeChild(int index) {
        if (index >= 0 && index < children.size()) {
            delete children[index];
            children.erase(children.begin() + index);
        }
    }
    // getter and setter methods for the label
    std::string getLabel() const { return label; }
    void setLabel(std::string value) { label = value; }
    // method to check if the node is terminal
    bool isTerminal() const {
        // node is terminal if it has no children
        return children.empty();
    }
};