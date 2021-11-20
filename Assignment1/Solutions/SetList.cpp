#include <limits>
#include <iostream>

struct Node {
	int value;
	Node* next;

    Node() {}
    Node(int value): value(value) {}
    
};


class SetList {
    private:
        Node* head = new Node(std::numeric_limits<int>::min()); 
        Node* tail = new Node(std::numeric_limits<int>::max());


    public:
        SetList() {
            head->next = tail;
        }

        ~SetList() {
            Node* node = NULL;

            while(node != tail) {
                node = head->next;
                delete head;
                head = node;
            }

            delete tail;
        }

        bool add(int value) {
            Node* pre, *cur;
            pre = head;
            cur = head->next;

            while(cur->value < value) {
                pre = cur;
                cur = cur->next;
            }

            // the value is in the set, fail to add
            if(cur->value == value) 
                return false;
            else {
                // the value is not in the set, add
                Node* node = new Node(value);
                node->next = cur;
                pre->next = node;
                return true;
            }
        }

        bool rmv(int value) {
            Node* pre, *cur;
            pre = head;
            cur = head->next;

            while(cur->value < value) {
                pre = cur;
                cur = cur->next;
            }

            // the value is in the set, remove
            if(cur->value == value) {
                pre->next = cur->next;
                delete cur;
                return true;
            } 
            else return false;
        }

        bool ctn(int value) {
            Node* pre, *cur;
            pre = head;
            cur = head->next;

            while(cur->value < value) {
                pre = cur;
                cur = cur->next;
            }

            // the value is in the set, 
            if(cur->value == value) {
                return true;
            } 
            else return false;
        }

        void printSetList() {
            Node *cur = head->next;
            std::cout << "[";
            while (cur != tail) {
                if(cur != head->next)
                    std::cout << ", ";
                std::cout << cur->value;
                cur = cur->next;
            }
            std::cout << "]" << std::endl;
        }

};