#include "PriorityQueue.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

PriorityQueue::PriorityQueue() : heap({}) {}

void PriorityQueue::push(Node *node, double distance) {
    // insert node and distance pair into heap
    heap.push_back(std::make_pair(node, distance));
    // heapify up
    heapifyUp();
}

void PriorityQueue::pop() {
    // swap first and last elements
    std::swap(heap[0], heap[heap.size() - 1]);
    // remove last element
    heap.pop_back();
    // heapify down
    heapifyDown();
}

void PriorityQueue::heapifyUp(int index) {
    // base case
    if (index == 0) {
        return;
    }

    int parentIndex = (index - 1) / 2;

    // if parent's distance is less than child's distance, swap
    if (heap[index].second > heap[parentIndex].second) {
        // swap parent and child
        std::swap(heap[index], heap[parentIndex]);
        // recursively heapify up
        heapifyUp(parentIndex);
    }
}

void PriorityQueue::heapifyDown(int index) {
    int size = heap.size();
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;

    // base case
}