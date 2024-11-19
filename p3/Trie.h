#ifndef TRIE_H
#define TRIE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Node.h"

class Trie {
   private:
    Node* root;
    int classifications;

    void validateInput(std::string input);
    bool isEmpty();
    std::string joinPath(const std::vector<std::string>& path);

   public:
    Trie();
    ~Trie();

    std::string load(std::string filename);
    std::string insert(std::string label);
    std::string classify(std::string key);
    std::string erase(std::string key);
    std::string print();
    std::string empty();
    std::string clear();
    std::string size();
};

#endif