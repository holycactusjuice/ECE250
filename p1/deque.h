#ifndef DEQUE_H
#define DEQUE_H

class Deque {
   private:
    int *array;
    int front;
    int back;
    int size;
    int capacity;

    int positiveMod(int n);
    void resize(int newCapacity);
    void checkSpaceAndResize();

   public:
    Deque();
    ~Deque();
    void pushBack(int val);
    int popFront();
    int popBack();
    int getSize() const;
    int getCapacity() const;
};

#endif