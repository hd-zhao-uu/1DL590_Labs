#ifndef NODE_H // include guard
#define NODE_H

#include <mutex>

template <class T>
struct Node {
	int value;
	Node* next;
    std::mutex lock;

    Node() {}
    Node(T value): value(value) {}
    
};

#endif
