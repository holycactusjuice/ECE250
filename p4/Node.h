#ifndef NODE_H
#define NODE_H

#include <climits>
#include <string>
#include <tuple>
#include <vector>

class Node {
   private:
    std::string id;
    std::string name;
    std::string type;
    std::vector<std::tuple<Node*, std::string, double>>
        relationships;  // each edge is {node, label, weight}
    bool queued;
    double distance;
    Node* parent;

    bool relationshipExists(std::string destinationId);

   public:
    Node(std::string id, std::string name, std::string type);

    // getters and setters for private variables
    std::string getId();
    std::string getName();
    std::string getType();
    void setName(std::string name);
    void setType(std::string type);
    bool getQueued();
    void setQueued(bool queued);
    double getDistance();
    void setDistance(double distance);
    Node* getParent();
    void setParent(Node* parent);
    std::vector<std::tuple<Node*, std::string, double>> getRelationships();

    void addRelationship(Node* destinationNode, std::string label,
                         double weight);
    void updateRelationship(std::string destinationId, std::string label,
                            double weight);
    void removeRelationship(std::string destinationId);
};

#endif