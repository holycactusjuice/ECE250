#ifndef PRIORTY_QUEUE_H
#define PRIORTY_QUEUE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Node.h"

class PriorityQueue {
   private:
    std::vector<std::pair<Node*, double>> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

   public:
    PriorityQueue();
    ~PriorityQueue();

    void push(Node*, double distance);
    void pop();
    std::pair<Node*, double> extractMax();
    void updateKey(Node*, double distance);
    bool empty();
};

#endif