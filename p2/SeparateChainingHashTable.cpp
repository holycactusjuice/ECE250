#include "SeparateChainingHashTable.h"

#include <string>

#include "HashNode.h"

SeparateChainingHashTable::SeparateChainingHashTable() : HashTable() {}

std::string SeparateChainingHashTable::store(unsigned int id,
                                             std::string data) {
    // we store in ascending order by id

    int loc = hash1(id);
    // remove ! from end of string
    data.pop_back();
    // get head node
    HashNode *curr = &map[loc];
    // CASE: empty
    // insert node at head
    if (curr->get_data() == "") {
        map[loc] = HashNode(id, data);
        return "success";
    }
    // CASE: node needs to be inserted at head
    if (curr->get_id() > id) {
        // insert node at head and move the old head to next
        HashNode *oldHead =
            new HashNode(curr->get_id(), curr->get_data(), curr->get_next());
        map[loc] = HashNode(id, data, oldHead);
        return "success";
    }
    // CASE: node needs to be inserted in the middle or at the end
    //
    while (curr->get_next() && curr->get_next()->get_id() <= id) {
        // move to next node
        curr = curr->get_next();
    }
    // if the id is already in the table, return failure
    if (curr->get_id() == id) return "failure";
    // insert
    HashNode *temp = curr->get_next();
    curr->set_next(new HashNode(id, data, temp));
    return "success";
}

std::string SeparateChainingHashTable::search(unsigned int id) {
    HashNode *node = findNode(id);
    if (!node) return "not found";

    return "found " + std::to_string(id) + " in " + std::to_string(hash1(id));
}

std::string SeparateChainingHashTable::deleteKey(unsigned int id) {
    int loc = hash1(id);
    // insert hash node
    HashNode *curr = &map[loc];
    // check if first node

    // CASE: empty
    // return failure
    if (curr->get_data() == "") return "failure";

    // CASE: node needs to be deleted at head
    if (curr->get_id() == id) {
        // delete the head node
        // if there is no next node, set the head to a new node
        HashNode *temp = curr->get_next() ? curr->get_next() : new HashNode();
        map[loc] = *temp;
        return "success";
    }

    // CASE: node needs to be deleted in the middle or at the end
    while (curr->get_next() && curr->get_next()->get_id() < id) {
        // move to next node
        curr = curr->get_next();
    }
    // if the id is not in the table, return failure
    if (curr->get_next() && curr->get_next()->get_id() != id) return "failure";
    // delete the node
    HashNode *temp = curr->get_next();
    curr->set_next(temp->get_next());

    return "success";
}

std::string SeparateChainingHashTable::corrupt(unsigned int id,
                                               std::string data) {
    data.pop_back();
    HashNode *node = findNode(id);
    if (!node) return "failure";
    node->corrupt(data);
    return "success";
}

std::string SeparateChainingHashTable::validate(unsigned int id) {
    HashNode *node = findNode(id);
    if (!node) return "failure";
    return node->validate() ? "valid" : "invalid";
}

std::string SeparateChainingHashTable::print(int i) {
    std::string res = "";
    // get the chain at index i
    HashNode *curr = &map[i];
    // iterate through the chain and append the id to the result string
    while (curr != nullptr && curr->get_data() != "") {
        res += std::to_string(curr->get_id()) + (curr->get_next() ? " " : "");
        curr = curr->get_next();
    }
    // if the chain is empty, return "chain is empty"
    if (res == "") res = "chain is empty";
    return res;
}

HashNode *SeparateChainingHashTable::findNode(unsigned int id) {
    int loc = hash1(id);
    HashNode *curr = &map[loc];

    // return empty node if the chain is empty
    if (curr->get_data() == "") return nullptr;

    while (curr != nullptr) {
        if (curr->get_id() == id) {
            return curr;
        }
        curr = curr->get_next();
    }

    return nullptr;
}