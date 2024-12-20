#include "deque.h"

#include <iostream>
#include <string>

Deque::Deque() : front(0), back(-1), size(0), capacity(4) {
    array = new int[capacity];
}

Deque::~Deque() {
    if (array != nullptr) {
        delete[] array;
        array = nullptr;
    }
}

int Deque::positiveMod(int n) { return (n % capacity + capacity) % capacity; }

void Deque::resize(int newCapacity) {
    int* newArray = new int[newCapacity];

    // copy elements to new array
    for (int i = 0; i < size; i++) {
        // need to account for wrap-around by using modulo
        newArray[i] = array[positiveMod(front + i)];
    }

    // deallocate old array
    delete[] array;
    // update array to newly created array
    array = newArray;
    // update other member variables
    front = 0;
    back = size - 1;  // size number of elements will have been added
    capacity = newCapacity;
}

void Deque::checkSpaceAndResize() {
    // if we have reached max capacity, double the capacity
    // if we have reached 1/4 capacity, halve the capacity
    if (size == capacity) {
        resize(capacity * 2);
    } else if (capacity > 2 && size <= capacity / 4) {
        resize(capacity / 2);
    }
}

void Deque::pushBack(int val) {
    back = positiveMod(back + 1);
    array[back] = val;
    size++;
    checkSpaceAndResize();
}

int Deque::popFront() {
    int val = array[front];
    front = positiveMod(front + 1);
    size--;
    checkSpaceAndResize();
    return val;
}

int Deque::popBack() {
    int val = array[back];
    back = positiveMod(back - 1);
    size--;
    checkSpaceAndResize();
    return val;
}

int Deque::getSize() const { return size; }

int Deque::getCapacity() const { return capacity; }