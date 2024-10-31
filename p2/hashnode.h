#ifndef HASH_NODE_H
#define HASH_NODE_H

#include <string>

class HashNode {
   private:
    unsigned int id;
    int checksum;
    std::string data;
    HashNode *next;

   public:
    HashNode();
    HashNode(unsigned int id, std::string data, HashNode *next);
    ~HashNode();
    unsigned int get_id();
    int get_checksum();
    int calc_checksum();
    std::string get_data();
    void corrupt(std::string data);
    bool validate();
};

#endif