#ifndef PRIORTY_QUEUE_H
#define PRIORTY_QUEUE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Node.h"

class PriorityQueue {
   private:
    std::vector<Node*> heap;

   public:
    void heapifyUp(int index);
    void heapifyDown(int index);
    PriorityQueue();
    void push(Node* node);
    void pop();
    int size();
    Node* extractMax();
    bool empty();
    void print();
};

#endif