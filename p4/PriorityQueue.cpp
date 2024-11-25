#include "PriorityQueue.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

PriorityQueue::PriorityQueue() : heap({}) {}

void PriorityQueue::push(Node *node) {
    // insert node and distance pair into heap
    heap.push_back(node);
    // heapify up from last element
    heapifyUp(heap.size() - 1);
}

void PriorityQueue::pop() {
    // swap first and last elements
    std::swap(heap[0], heap[heap.size() - 1]);
    // remove last element
    heap.pop_back();
    // heapify down from root
    heapifyDown(0);
}

int PriorityQueue::size() { return heap.size(); }

void PriorityQueue::heapifyUp(int index) {
    // base case
    if (index <= 0) {
        return;
    }

    int parentIndex = (index - 1) / 2;

    // if parent's distance is less than child's distance, swap
    if (heap[index]->getDistance() > heap[parentIndex]->getDistance()) {
        // swap parent and child
        std::swap(heap[index], heap[parentIndex]);
        // recursively heapify up
        heapifyUp(parentIndex);
    }
}

void PriorityQueue::heapifyDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int best = index;

    // if left child exists and is greater than parent, update largest index
    if (left < heap.size() &&
        heap[left]->getDistance() > heap[best]->getDistance()) {
        best = left;
    }

    // if right child exists and is greater than parent, update largest index
    if (right < heap.size() &&
        heap[right]->getDistance() > heap[best]->getDistance()) {
        best = right;
    }

    // if largest index is not parent, swap parent and child
    if (best != index) {
        std::swap(heap[index], heap[best]);
        // recursively heapify down
        heapifyDown(best);
    }
}

Node *PriorityQueue::extractMax() {
    // get max element
    auto max = heap[0];
    // remove max element
    pop();

    return max;
}

bool PriorityQueue::empty() { return heap.empty(); }

void PriorityQueue::print() {
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Heap:" << std::endl;
    for (Node *node : heap) {
        std::cout << node->getId() << " " << node->getDistance() << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl;
}