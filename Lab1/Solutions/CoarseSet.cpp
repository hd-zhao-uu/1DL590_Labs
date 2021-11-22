#include <limits>
#include <iostream>
#include <mutex>
#include <vector>
#include "LinearizedSeq.cpp"
#include "Node.h"



class CoarseSet {
    private:
        Node<int>* head = new Node<int>(std::numeric_limits<int>::min()); 
        Node<int>* tail = new Node<int>(std::numeric_limits<int>::max());
        std::mutex mutex;
        std::vector<std::pair<int, operation>> seq;
        int threadId;


    public:
        CoarseSet() {
            head->next = tail;
        }

        CoarseSet(std::vector<std::pair<int, operation>>& sharedSeq) {
            head->next = tail;
            seq = sharedSeq;
        }

        ~CoarseSet() {
            Node<int>* node = NULL;

            while(node != tail) {
                node = head->next;
                delete head;
                head = node;
            }

            delete tail;
        }

        bool add(int value) {
            mutex.lock();
            Node<int>* pre, *cur;
            pre = head;
            cur = head->next;

            while(cur->value < value) {
                pre = cur;
                cur = cur->next;
            }

            // the value is in the set, fail to add
            if(cur->value == value) {
                mutex.unlock();
                return false;
            }
            else {
                // the value is not in the set, add
                Node<int>* node = new Node<int>(value);
                node->next = cur;
                pre->next = node;
                mutex.unlock();
                return true;
            }
        }

        bool rmv(int value) {
            mutex.lock();
            Node<int>* pre, *cur;
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
                mutex.unlock();
                return true;
            } 
            else {
                mutex.unlock();
                return false;
            }
        }

        bool ctn(int value) {
            mutex.lock();
            Node<int>* pre, *cur;
            pre = head;
            cur = head->next;

            while(cur->value < value) {
                pre = cur;
                cur = cur->next;
            }

            // the value is in the set, 
            if(cur->value == value) {
                mutex.unlock();
                return true;
            } 
            else {
                mutex.unlock();
                return false;
            }
        }

        //---------------------------------------------------------------
        bool add(int value, int threadId) {
            mutex.lock();
            Node<int>* pre, *cur;
            pre = head;
            cur = head->next;

            while(cur->value < value) {
                pre = cur;
                cur = cur->next;
            }

            // the value is in the set, fail to add
            if(cur->value == value) {
                seq.push_back({threadId, operation{methodname::add, value, false}});
                mutex.unlock();
                return false;
            }
            else {
                // the value is not in the set, add
                Node<int>* node = new Node<int>(value);
                node->next = cur;
                pre->next = node;
                seq.push_back({threadId, operation{methodname::add, value, false}});
                mutex.unlock();
                return true;
            }
        }

        bool rmv(int value, int threadId) {
            mutex.lock();
            Node<int>* pre, *cur;
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
                seq.push_back({threadId, operation{methodname::rmv, value, true}});
                mutex.unlock();
                return true;
            } 
            else {
                seq.push_back({threadId, operation{methodname::rmv, value, false}});
                mutex.unlock();
                return false;
            }
        }

        bool ctn(int value, int threadId) {
            mutex.lock();
            Node<int>* pre, *cur;
            pre = head;
            cur = head->next;

            while(cur->value < value) {
                pre = cur;
                cur = cur->next;
            }

            // the value is in the set, 
            if(cur->value == value) {
                seq.push_back({threadId, operation{methodname::ctn, value, true}});
                mutex.unlock();
                return true;
            } 
            else {
                seq.push_back({threadId, operation{methodname::ctn, value, false}});
                mutex.unlock();
                return false;
            }
        }

        void printCoarseSet() {
            Node<int> *cur = head->next;
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


