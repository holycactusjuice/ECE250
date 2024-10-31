#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

class HashTable {
   private:
    int hashType;
    int size;
    int hash1(int k);
    int hash2(int k);
    std::vector<std::string> map;

   public:
    HashTable();
    ~HashTable();
    std::string newTable(int size, int hashType);
    std::string store(int id, std::string charstring);
    std::string search(int id);
    std::string deleteKey(int id);
    std::string corrupt(int id, std::string charstring);
    std::string validate(int id);
    std::string print(int i);
};

#endif