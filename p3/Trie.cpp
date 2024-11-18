#include "Trie.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "IllegalException.h"
#include "Node.h"
#include "ece250_socket.h"

Trie::Trie() {
    root = new Node();
    classifications = 0;
}

Trie::~Trie() { delete root; }

// Input validator, throws exception if input contains uppercase characters
void Trie::validate_input(std::string input) {
    for (char c : input) {
        if (isupper(c)) {
            throw IllegalException();
        }
    }
}

// Loading file into trie
void Trie::load(std::string filename) {
    std::ifstream myReadFile(filename);
    std::string label;

    // Insert all labels into trie
    while (std::getline(myReadFile, label)) {
        insert(label, false);
    }

    std::cout << "success" << std::endl;
    myReadFile.close();
}

// Function to insert a label into the trie, print_output determins whether to
// print success messages (Not used in load)
void Trie::insert(std::string classification, bool print_output = true) {
    Node* currentNode = root;         // Root node
    std::vector<std::string> labels;  // Contains the list of labels to insert
    std::istringstream stream(classification);

    try {
        validate_input(classification);
    }

    catch (IllegalException& e) {
        std::cout << "illegal argument" << std::endl;
        return;
    }

    // Check if no input was passed
    if (classification.empty()) {
        if (print_output) std::cout << "failure" << std::endl;
        return;
    }

    // Boolean val to check whether a new node was created, if no new node was
    // created, insertion failed
    bool createdNewNode = false;

    // Split the input into labels
    std::string label;
    while (std::getline(stream, label, ',')) {
        labels.push_back(label);
    }

    // Iterae through the labels for insertion
    for (size_t i = 0; i < labels.size(); i++) {
        label = labels[i];
        bool exist = false;

        // Checks if the label already exists in the children of the current
        // node
        for (Node* child : currentNode->getChildren()) {
            // If the label exists, set the current node to the child node and
            // break
            if (child->getLabel() == label) {
                currentNode = child;
                exist = true;
                break;
            }
        }

        // If the label didn't exist, this means we're creating a new child node
        if (!exist) {
            // If currentNode is terminal and we are adding a child, unset
            // terminal as it's no longer a leaf node
            if (currentNode->getIsTerminal()) {
                currentNode->setTerminal(false);
            }

            // Create a new node and set the label
            Node* newNode = new Node();
            newNode->setLabel(label);
            currentNode->getChildren().push_back(newNode);
            currentNode = newNode;
            createdNewNode = true;  // New node had been created
        }
        // If the label exists, set the current node to the child node
        else {
            // If currentNode is terminal and we are not at the last label,
            // unset terminal as it's no longer a leaf node by the next
            // iteration
            if (currentNode->getIsTerminal() && i < labels.size() - 1) {
                currentNode->setTerminal(false);
            }
        }
    }

    // Here we check for 2 cases:
    // 1. If the last node is a terminal node, and no new nodes were created,
    // insertion failed
    // 2. If the last node is not a terminal node, insertion failed as it's not
    // a leaf node
    if (!createdNewNode && currentNode->getIsTerminal() ||
        !currentNode->getChildren().empty()) {
        if (print_output) std::cout << "failure" << std::endl;
        return;
    }

    // Set last node as terminal and update the classifications count
    if (!currentNode->getIsTerminal()) {
        currentNode->setTerminal(true);
        classifications++;
    }

    if (print_output) std::cout << "success" << std::endl;
}

// Classify function to classify a given input
void Trie::classify(std::string input) {
    Node* currentNode = root;
    std::vector<std::string> output;

    try {
        validate_input(input);
    }

    catch (IllegalException& e) {
        std::cout << "illegal argument" << std::endl;
        return;
    }

    // While current node is not a terminal node
    while (!currentNode->getIsTerminal()) {
        // Checks if there no more children
        if (currentNode->getChildren().empty()) {
            break;  // Exit if we reach a node with no children
        }

        // Adds all possible labels to a string for classification
        std::string candidate_labels = "";
        for (Node* child : currentNode->getChildren()) {
            candidate_labels += child->getLabel() + ",";
        }

        // Remove trailing comma if exists
        if (!candidate_labels.empty() && candidate_labels.back() == ',') {
            candidate_labels.pop_back();
        }

        // Classify the input between the candidate labels
        std::string label = labelText(input, candidate_labels);
        bool found = false;

        // Jump to the next node based on classification
        for (Node* child : currentNode->getChildren()) {
            if (child->getLabel() == label) {
                currentNode = child;
                output.push_back(label);
                found = true;
                break;
            }
        }

        if (!found) {
            break;
        }
    }

    std::string result = "";
    for (std::string label : output) {
        result += label + ",";
    }

    if (!result.empty() && result.back() == ',') {
        result.pop_back();
    }

    std::cout << result << std::endl;
}

void Trie::erase(std::string classification) {
    std::vector<std::string> labels;
    std::string label;
    std::istringstream stream(classification);

    try {
        validate_input(classification);
    }

    catch (IllegalException& e) {
        std::cout << "illegal argument" << std::endl;
        return;
    }

    // Check if trie is empty
    if (this->classifications == 0) {
        std::cout << "failure" << std::endl;
        return;
    }

    while (std::getline(stream, label, ',')) {
        labels.push_back(label);
    }

    if (labels.size() == 0 || classifications == 0) {
        std::cout << "failure" << std::endl;
        return;
    }

    // Track the path to the node to be deleted
    std::vector<Node*> path;
    std::vector<int> childIndex;  // Track the index of the child in the parent
                                  // node for the level traversed
    Node* currentNode = root;
    path.push_back(currentNode);

    // Iteratively traverse to find the node to delete
    for (std::string label : labels) {
        bool found = false;
        for (int i = 0; i < currentNode->getChildren().size(); i++) {
            if (currentNode->getChildren()[i] != nullptr &&
                currentNode->getChildren()[i]->getLabel() == label) {
                currentNode = currentNode->getChildren()[i];
                path.push_back(currentNode);
                childIndex.push_back(i);
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "failure" << std::endl;
            return;
        }
    }

    // Make sure it's a leaf node (has no children) and is terminal else
    // terminate
    if (!currentNode->getChildren().empty() || !currentNode->getIsTerminal()) {
        std::cout << "failure" << std::endl;
        return;
    }

    // Delete the leaf node
    Node* parentNode = path[path.size() - 2];
    int lastIndex = childIndex.back();

    // Use the new removeChild method
    parentNode->removeChild(lastIndex);
    classifications--;

    // Check if parent needs to become terminal
    // Start from the last parent and work up (excluding root)
    for (int i = path.size() - 2; i > 0; i--) {
        Node* node = path[i];
        if (node->getChildren().empty() && !node->getIsTerminal()) {
            node->setTerminal(true);
            classifications++;
            break;  // Only the first empty parent becomes terminal
        }
    }

    std::cout << "success" << std::endl;
}

// Use DFS to print all the labels in the trie
void Trie::print() {
    if (this->classifications == 0) {
        std::cout << "trie is empty" << std::endl;
        return;
    }

    // We keep a stack for DFS and a vector for path
    std::vector<Node*> stack;
    std::vector<std::vector<std::string>> paths;

    // Push root node and the empty path
    stack.push_back(root);
    paths.push_back(std::vector<std::string>());
    bool first_classification = true;

    while (!stack.empty()) {
        Node* currentNode = stack.back();
        std::vector<std::string> currentPath = paths.back();
        stack.pop_back();
        paths.pop_back();

        // If current node is terminal, and not the root node, print the path
        if (currentNode->getIsTerminal()) {
            if (!first_classification) {
                std::cout << "_";
            }
            first_classification = false;

            // Print the path (the actual classification)
            for (size_t i = 0; i < currentPath.size(); i++) {
                std::cout << currentPath[i];
                if (i != currentPath.size() - 1) {
                    std::cout << ",";
                }
            }
        }

        // Push children to stack
        for (int i = currentNode->getChildren().size() - 1; i >= 0; i--) {
            if (currentNode->getChildren()[i] != nullptr) {
                stack.push_back(currentNode->getChildren()[i]);

                // Creates new path by copying current path and adding the new
                // label
                std::vector<std::string> newPath = currentPath;
                newPath.push_back(currentNode->getChildren()[i]->getLabel());
                paths.push_back(newPath);
            }
        }
    }
    std::cout << "_";
    std::cout << std::endl;
}

void Trie::empty() {
    if (this->classifications == 0) {
        std::cout << "empty 1" << std::endl;
    } else {
        std::cout << "empty 0" << std::endl;
    }
}

void Trie::clear() {
    delete root;
    root = new Node();
    this->classifications = 0;
    std::cout << "success" << std::endl;
}

void Trie::size() {
    std::cout << "number of classifications is " << this->classifications
              << std::endl;
}