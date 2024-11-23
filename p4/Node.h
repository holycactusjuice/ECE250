#ifndef NODE_H
#define NODE_H

#include <string>
#include <tuple>
#include <vector>

class Node {
   private:
    std::string id;
    std::string name;
    std::string type;
    std::vector<std::tuple<std::string, std::string, double>>
        relationships;  // each edge is {id, label, weight}

   public:
    Node(std::string id, std::string name, std::string type);
    std::string getId();
    std::string getName();
    std::string getType();
    void setName(std::string name);
    void setType(std::string type);

    std::vector<std::tuple<std::string, std::string, double>>
    getRelationships();
    void addRelationship(std::string destinationId, std::string label,
                         double weight);
    void updateRelationship(std::string destinationId, std::string label,
                            double weight);
    void removeRelationship(std::string destinationId);
};

#endif