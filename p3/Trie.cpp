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

Trie::Trie() : root(new Node()), classifications(0) {}

Trie::~Trie() { delete root; }

void Trie::validateInput(std::string input) {
    for (char c : input) {
        if (isupper(c)) throw IllegalException();
    }
}

std::string Trie::load(std::string filename) {
    std::ifstream dataFile(filename);
    std::string label;

    while (std::getline(dataFile, label)) insert(label);

    dataFile.close();

    return "success";
}

std::string Trie::insert(std::string classification) {
    if (classification.empty()) return "failure";

    try {
        validateInput(classification);
    } catch (IllegalException&) {
        return "illegal argument";
    }

    std::vector<std::string> labels;
    std::istringstream stream(classification);
    std::string label;

    while (std::getline(stream, label, ',')) {
        labels.push_back(label);
    }

    Node* curr = root;
    bool createdNode = false;

    for (const std::string& label : labels) {
        bool exists = false;

        for (Node* child : curr->getChildren()) {
            if (child->getLabel() == label) {
                curr = child;
                exists = true;
                break;
            }
        }
        if (!exists) {
            Node* newNode = new Node();
            newNode->setLabel(label);
            curr->addChild(newNode);
            curr = newNode;
            createdNode = true;
        }
    }

    if (!createdNode && curr->isTerminal() || !curr->getChildren().empty()) {
        return "failure";
    }

    if (!curr->isTerminal()) classifications++;

    return "success";
}

std::string Trie::classify(std::string input) {
    try {
        validateInput(input);
    } catch (IllegalException& e) {
        return "illegal argument";
    }

    Node* curr = root;
    std::vector<std::string> resultVector;

    while (!curr->isTerminal()) {
        if (curr->getChildren().empty()) break;

        std::string possibleLabels;
        for (const auto& child : curr->getChildren())
            possibleLabels += child->getLabel() + ",";
        possibleLabels.pop_back();

        std::string targetLabel = labelText(input, possibleLabels);

        bool found = false;

        for (const auto& child : curr->getChildren()) {
            if (child->getLabel() != targetLabel) continue;
            curr = child;
            resultVector.push_back(targetLabel);
            found = true;
        }

        if (!found) break;
    }

    std::string result = "";
    for (int i = 0; i < resultVector.size(); i++) {
        result += resultVector[i];
        if (i < resultVector.size() - 1) result += ",";
    }

    return result;
}

std::string Trie::erase(std::string classification) {
    try {
        validateInput(classification);
    } catch (IllegalException& e) {
        return "illegal argument";
    }

    if (isEmpty()) return "failure";

    std::vector<std::string> labels;
    std::istringstream stream(classification);
    std::string label;

    while (std::getline(stream, label, ',')) labels.push_back(label);

    if (labels.empty() || isEmpty()) return "failure";

    Node* curr = root;
    std::vector<Node*> path{curr};
    std::vector<int> childIndex;

    for (const std::string& label : labels) {
        bool found = false;
        const auto& children = curr->getChildren();
        for (int i = 0; i < children.size(); i++) {
            if (children[i] && children[i]->getLabel() == label) {
                curr = children[i];
                path.push_back(curr);
                childIndex.push_back(i);
                found = true;
                break;
            }
        }

        if (!found) return "failure";
    }

    if (!curr->getChildren().empty() || !curr->isTerminal()) return "failure";

    Node* parent = path[path.size() - 2];
    int lastIndex = childIndex.back();

    parent->removeChild(lastIndex);
    classifications--;

    for (int i = path.size() - 2; i > 0; i--) {
        Node* node = path[i];
        if (node->getChildren().empty() && !node->isTerminal()) {
            classifications++;
            break;
        }
    }

    return "success";
}

#include <stack>

std::string Trie::print() {
    if (isEmpty()) return "trie is empty";

    std::stack<Node*> nodeStack;
    nodeStack.push(root);

    std::stack<std::vector<std::string>> pathStack;
    pathStack.push({});

    std::string result = "";

    while (!nodeStack.empty()) {
        Node* curr = nodeStack.top();
        nodeStack.pop();

        std::vector<std::string> path = pathStack.top();
        pathStack.pop();

        if (curr->isTerminal()) {
            if (result != "") result += "_";

            for (int i = 0; i < path.size(); i++) {
                result += path[i];
                if (i != path.size() - 1) result += ",";
            }
        }

        const auto& children = curr->getChildren();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            nodeStack.push(*it);

            std::vector<std::string> newPath = path;
            newPath.push_back((*it)->getLabel());
            pathStack.push(newPath);
        }
    }
    result += "_";
    return result;
}

std::string Trie::empty() {
    return "empty " + std::to_string(isEmpty() ? 1 : 0);
}

std::string Trie::clear() {
    delete root;
    root = new Node();
    classifications = 0;
    return "success";
}

std::string Trie::size() {
    return "number of classifications is " + std::to_string(classifications);
}

bool Trie::isEmpty() { return classifications == 0; }