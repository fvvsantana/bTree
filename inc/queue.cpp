#include "queue.hpp"

// constructor
Queue::Queue() {
    // number of elements is 0
    size = 0;

    // initial capacity is 10
    capacity = 10;

    array = new NodeInfo[capacity];
}

// destructor
Queue::~Queue() {
    delete[] array;
}

// double the current capacity to improve efficiency
void Queue::resize() {

    // create new array with twice the capacity
    capacity = capacity * 2;
    NodeInfo* newArray = new NodeInfo[capacity];

    // copy the original elements
    for (int i = 0; i < size; i++)
        newArray[i] = array[i];

    // delete old array and change the reference to the new array
    delete[] array;
    array = newArray;
}

// add element at the end of the queue
void Queue::push(int nodeRrn, int level) {
    // check if is needed to resize
    if (size == capacity)
        resize();

    // add element at the end and update size
    array[size] = NodeInfo(nodeRrn, level);
    size++;
}

// remove and return the first element from the queue
void Queue::pop(int &rrn, int &level) {
    // get first value
    NodeInfo node = array[0];

    // move each value one position to the left
    for (int i = 0; i < size-1; i++)
        array[i] = array[i+1];

    // reduce size and return
    size--;
    rrn = node.rrn;
    level = node.level;
}

// return true if queue is empty
bool Queue::isEmpty() {
    return size == 0;
}
