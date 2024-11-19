#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Node {
   private:
    std::vector<Node*> children;
    std::string label;

   public:
    Node();
    ~Node();

    const std::vector<Node*>& getChildren() const;
    void addChild(Node* child);
    void removeChild(int index);

    std::string getLabel() const;
    void setLabel(std::string value);

    bool isTerminal() const;
};

#endif