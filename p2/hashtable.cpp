#include "hashtable.h"

#include <iostream>
#include <string>
#include <vector>

HashTable::HashTable() : size(0), hashType(-1) {}

std::string HashTable::newTable(int size, int hashType) {
    size = size;
    hashType = hashType;
    map = std::vector<std::string>(size, "");
    return "success";
}

int HashTable::hash1(int k) { return k % size; }

int HashTable::hash2(int k) {
    int res = (k / size) % size;
    // add 1 to result if value is even
    res += (res % 2 == 0) ? 1 : 0;
    return res;
}

std::string HashTable::store(int id, std::string charstring) {
    // remove ! from end of string
    charstring.pop_back();

    // get primary hash
    int h1 = hash1(id);
    // while hash is occupied at hash value, add secondary hash
    int h2 = hash2(id);
    while (map[h1].) }
