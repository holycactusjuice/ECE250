#include "OpenAddressingHashTable.h"

#include <iostream>
#include <string>

#include "HashNode.h"

OpenAddressingHashTable::OpenAddressingHashTable() : HashTable() {}

int OpenAddressingHashTable::hash2(int k) {
    int res = (k / size) % size;
    // add 1 to result if value is even
    res += (res % 2 == 0) ? 1 : 0;
    return res;
}

int OpenAddressingHashTable::findKey(unsigned int id) {
    // return -1 if not found
    // return index if found

    // get hash values
    int hash = hash1(id);
    int offset = hash2(id);

    // Check the first position
    if (map[hash].get_data().size() > 0 && map[hash].get_id() == id) {
        return hash;
    }

    int originalHash = hash;
    // Start probing from the next position
    hash = (hash + offset) % size;

    // loop while table is occupied at hash
    while (map[hash].get_data().size() > 0 && hash != originalHash) {
        if (map[hash].get_id() == id) {
            return hash;
        }
        hash = (hash + offset) % size;
    }

    return -1;
}

std::string OpenAddressingHashTable::store(unsigned int id, std::string data) {
    int hash = hash1(id);
    int offset = hash2(id);

    // check if the head node has the same id as the one we are trying to insert
    if (map[hash].get_id() == id && map[hash].get_data() != "")
        return "failure";
    // loop while table is occupied at hash
    while (map[hash].get_data().size() > 0) {
        hash = (hash + offset) % size;
        // if we have reached the original hash value, return failure
        if (hash == hash1(id)) return "failure";
        // if this node has the same id as the one we are trying to insert,
        // return failure
        if (map[hash].get_id() == id) return "failure";
    }
    // remove ! from end of string
    data.pop_back();
    // create HashNode object with key and payload
    HashNode hn(id, data);
    // insert hash node
    map[hash] = hn;
    return "success";
}

std::string OpenAddressingHashTable::search(unsigned int id) {
    int loc = findKey(id);
    return loc == -1
               ? "not found"
               : ("found " + std::to_string(id) + " in " + std::to_string(loc));
}

std::string OpenAddressingHashTable::deleteKey(unsigned int id) {
    int loc = findKey(id);
    if (loc == -1) return "failure";
    map[loc] = HashNode();
    return "success";
}

std::string OpenAddressingHashTable::corrupt(unsigned int id,
                                             std::string data) {
    // search key
    // return failure if not found
    int loc = findKey(id);
    if (loc == -1) return "failure";

    // remove ! from end of string
    data.pop_back();

    // get file object at loc
    HashNode &file = map[loc];
    // corrupt file
    file.corrupt(data);
    return "success";
}

std::string OpenAddressingHashTable::validate(unsigned int id) {
    // search key
    // return failure if not found
    int loc = findKey(id);
    if (loc == -1) return "failure";

    bool isValid = map[loc].validate();
    return isValid ? "valid" : "invalid";
}

std::string OpenAddressingHashTable::print(int i) {
    // this function is only for debugging purposes
    // print file at index i
    return std::to_string(i) + ": " + map[i].get_data();
}