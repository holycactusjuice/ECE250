#ifndef OPEN_ADDRESSING_HASH_TABLE_H
#define OPEN_ADDRESSING_HASH_TABLE_H

#include <string>

#include "HashNode.h"
#include "HashTable.h"

class OpenAddressingHashTable : public HashTable {
   public:
    OpenAddressingHashTable();
    std::string store(unsigned int id, std::string data) override;
    std::string search(unsigned int id) override;
    std::string deleteKey(unsigned int id) override;
    std::string corrupt(unsigned int id, std::string data) override;
    std::string validate(unsigned int id) override;
    std::string print(int i) override;

   private:
    int findKey(unsigned int id);
    int hash2(int k);
};

#endif