#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

#include "HashNode.h"

class HashTable {
   protected:
    int size;
    std::vector<HashNode> map;

    int hash1(int k);

   public:
    HashTable();
    std::string newTable(int size);
    virtual std::string store(unsigned int id, std::string charstring) = 0;
    virtual std::string search(unsigned int id) = 0;
    virtual std::string deleteKey(unsigned int id) = 0;
    virtual std::string corrupt(unsigned int id, std::string charstring) = 0;
    virtual std::string validate(unsigned int id) = 0;
    virtual std::string print(int i) = 0;
};

#endif