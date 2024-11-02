#include "HashTable.h"

#include <string>
#include <vector>

#include "HashNode.h"

HashTable::HashTable() : size(0) {}

std::string HashTable::newTable(int size) {
    this->size = size;
    map = std::vector<HashNode>(size, HashNode());
    return "success";
}

int HashTable::hash1(int k) { return k % size; }
