#include "HashNode.h"

#include <string>

HashNode::HashNode() : id(0), checksum(-1), data(""), next(nullptr) {}

HashNode::~HashNode() {
    delete next;  // Will recursively delete the chain
    next = nullptr;
}

HashNode::HashNode(unsigned int id, std::string data)
    : id(id), data(data), next(nullptr) {
    update_checksum();
}

HashNode::HashNode(unsigned int id, std::string data, HashNode *next)
    : id(id), data(data), next(next) {
    update_checksum();
}

unsigned int HashNode::get_id() { return id; }

int HashNode::get_checksum() { return checksum; }

int HashNode::calc_checksum() {
    int charsum = 0;
    for (const char c : data) charsum += c;
    return charsum % 256;
}

HashNode *HashNode::get_next() { return next; }

void *HashNode::set_next(HashNode *next) {
    this->next = next;
    return this;
}

void HashNode::update_checksum() { checksum = calc_checksum(); }

std::string HashNode::get_data() { return data; }

void HashNode::corrupt(std::string charstring) {
    for (char &c : charstring) c = 0;
}

bool HashNode::validate() { return checksum == calc_checksum(); }