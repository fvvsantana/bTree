#ifndef QUEUE_HPP
#define QUEUE_HPP

class Queue {
private:
    // the capacity of elements on queue
    int capacity;

    // number of elements on queue
    int size;

    // each queue element will be a NodeInfo object, containing the rrn and the level of a node
    typedef struct NodeInfo {
        int rrn;
        int level;

        NodeInfo(){}

        NodeInfo(int value1, int value2) {
            rrn = value1;
            level = value2;
        }
    } NodeInfo;

    NodeInfo* array;

    void resize();

public:
    // constructor
    Queue();

    // destructor
    ~Queue();

    void push(int nodeRrn, int level);

    void pop(int &rrn, int &level);

    bool isEmpty();
};

#endif /* end of include guard: QUEUE_HPP */
