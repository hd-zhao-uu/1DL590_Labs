#ifndef NODE_H // include guard
#define NODE_H

template <class T>
struct Node {
	int value;
	Node* next;

    Node() {}
    Node(T value): value(value) {}
    
};

#endif
