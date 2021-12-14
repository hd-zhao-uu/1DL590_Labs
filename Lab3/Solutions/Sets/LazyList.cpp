#include <limits>
#include <iostream>
#include <mutex>
#include <vector>
#include "Operation.h"
#include "Node.h"

class LazyList{
    private:
        Node* head = new Node(std::numeric_limits<int>::min()); 
        Node* tail = new Node(std::numeric_limits<int>::max());
        std::vector<std::pair<int, Operation>> seq;
        std::mutex mtx; // Only for vector<Operation> sharedSeq

        // locate pointers
        std::pair<Node*, Node*> locate(int e) {
            thread_local Node* p, *c;
            while(true) {
                p = head;
                c = head->next;
                while(c->value < e) {
                    p = c;
                    c = c->next;
                }
                p->lock.lock();
                c->lock.lock();

                if (!p->mark && !c->mark && p->next == c) {
                    return {p, c};
                }
                else{
                    p->lock.unlock();
                    c->lock.unlock();
                }
            }
        }


    public:
        LazyList() {
            head->next = tail;
        }

        LazyList(std::vector<std::pair<int, Operation>>& sharedSeq) { 
            head->next = tail; 
            seq = sharedSeq;
        }

        ~LazyList() {
            Node* node = NULL;

            while(node != tail) {
                node = head->next;
                delete head;
                head = node;
            }

            delete tail;
        }

        bool add(int value) {
            bool ret;

            thread_local Node* p, *c;
            std::tie(p, c) = locate(value); // locate p and c

            if(c->value != value) {
                Node *node = new Node(value);
                node->next = c;
                p->next = node;
                ret = true;
            }
            else ret = false;
            
            p->lock.unlock();
            c->lock.unlock();
            
            return ret;
        }

        bool rmv(int value) {
            bool ret;

            thread_local Node* p, *c;
            std::tie(p, c) = locate(value); // locate p and c

            if(c->value == value) {
                // remove logically
                c->mark = true; 

                // remove physically
                p->next = c->next;
                ret = true;
            }
            else ret = false;

            p->lock.unlock();
            c->lock.unlock();
            return ret;
        }

        bool ctn(int value) {
            bool ret;

            thread_local Node* c;
            c = head;
            while(c->value < value) {
                c = c ->next;
            }
            bool mark = c->mark;
            if(!mark && c->value == value)
                ret = true; 
            else ret = false;
            
            return ret;
        }

        //////////////////////////////////////////////////////////////////////
        bool add(int value, int threadId) {
            bool ret;

            thread_local Node* p, *c;
            std::tie(p, c) = locate(value); // locate p and c

            if(c->value != value) {
                Node* node = new Node(value);
                node->next = c;
                p->next = node;
                ret = true;
            }
            else ret = false;

            mtx.lock();
            seq.push_back({threadId, Operation{methodname::add, value, ret}});
            mtx.unlock();
            
            p->lock.unlock();
            c->lock.unlock();
            
            return ret;
        }

        bool rmv(int value, int threadId) {
            bool ret;

            thread_local Node* p, *c;
            std::tie(p, c) = locate(value); // locate p and c

            if(c->value == value) {
                // remove logically
                c->mark = true; 

                // remove physically
                p->next = c->next;
                ret = true;
            }
            else ret = false;

            mtx.lock();
            seq.push_back({threadId, Operation{methodname::rmv, value, ret}});
            mtx.unlock();

            p->lock.unlock();
            c->lock.unlock();
            return ret;
        }

        bool ctn(int value, int threadId) {
            bool ret;

            thread_local Node* c;
            c = head;
            while(c->value < value) {
                c = c ->next;
            }
            bool mark = c->mark;
            if(!mark && c->value == value)
                ret = true; 
            else ret = false;

            mtx.lock();
            seq.push_back({threadId, Operation{methodname::ctn, value, ret}});
            mtx.unlock();
            
            return ret;
        }

};


