#include "hashnode.h"

#include <string>

HashNode::HashNode() : id(0), checksum(-1), data(""), next(nullptr) {}

HashNode::HashNode(unsigned int id, std::string data, HashNode *next)
    : id(id), data(data), next(next) {
    checksum = calc_checksum();
}

HashNode::~HashNode() { next = nullptr; }

unsigned int HashNode::get_id() { return id; }

int HashNode::get_checksum() { return checksum; }
