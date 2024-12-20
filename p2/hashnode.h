#ifndef HASH_NODE_H
#define HASH_NODE_H

#include <string>

class HashNode {
   private:
    unsigned int id;
    int checksum;
    std::string data;
    HashNode *next;
    int calc_checksum();

   public:
    HashNode();
    HashNode(unsigned int id, std::string data);
    HashNode(unsigned int id, std::string data, HashNode *next);
    ~HashNode();

    unsigned int get_id();
    int get_checksum();
    HashNode *get_next();
    void set_next(HashNode *next);
    std::string get_data();

    void update_checksum();
    void corrupt(std::string data);
    bool validate();
};

#endif