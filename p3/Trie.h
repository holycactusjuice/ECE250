#ifndef TRIE_H
#define TRIE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "node.h"

class Trie {
   protected:
    Node* root;           // Root of the trie
    int classifications;  // # of classifications, used for size

   public:
    Trie();   // Constructor
    ~Trie();  // Destructor

    // Function declarations for Trie
    void load(std::string filename);
    void insert(std::string label, bool print_output);
    void classify(std::string key);
    void erase(std::string key);
    void print();
    void empty();
    void size();
    void clear();
    void validate_input(std::string input);
};

#endif