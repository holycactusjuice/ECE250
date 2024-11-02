#ifndef SEPARATE_CHAINING_HASH_TABLE_H
#define SEPARATE_CHAINING_HASH_TABLE_H

#include <string>

#include "HashNode.h"
#include "HashTable.h"

class SeparateChainingHashTable : public HashTable {
   public:
    SeparateChainingHashTable();
    std::string store(unsigned int id, std::string data) override;
    std::string search(unsigned int id) override;
    std::string deleteKey(unsigned int id) override;
    std::string corrupt(unsigned int id, std::string data) override;
    std::string validate(unsigned int id) override;
    std::string print(int i) override;

   private:
    HashNode* findNode(unsigned int id);
};

#endif