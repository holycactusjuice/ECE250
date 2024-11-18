#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <iostream>
#include <vector>

class Node {
   private:
    std::vector<Node> children;  // Children of the node
    std::string label;           // Label of the node
    bool isTerminal;             // Indicates if the node is a terminal node

   public:
    std::vector<Node>& getChildren() {
        return children;
    }  // Get children of the node
    std::string getLabel() { return label; }  // Get label of the node
    void setLabel(std::string value) {
        label = value;
    }  // Set label of the node
    bool getIsTerminal() { return isTerminal; }  // Get if the node is terminal
    void setTerminal(bool value) {
        isTerminal = value;
    }  // Set label of the node
    void removeChild(int index);  // Remove a child from the node

    Node();   // Constructor
    ~Node();  // Destructor
};

#endif