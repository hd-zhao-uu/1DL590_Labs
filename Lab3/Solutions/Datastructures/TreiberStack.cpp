
#include <mutex>
#include <vector>
#include <atomic>
#include <string>
#include "StackOperation.h"

template <typename T>
struct TNode {
    T value;
    std::atomic<TNode*> next;

    TNode() {}
    TNode(T value) : value(value) {}
};

class TreiberStack {
    private:
        std::atomic<TNode<std::string>*> top;
        std::vector<std::pair<int, StackOperation>> seq;
        std::atomic<int> sz;
        std::mutex mtx;

    public:
        TreiberStack(){
            // top.store(new Node());
        }

        TreiberStack(std::vector<std::pair<int, StackOperation>>& sharedSeq){
            // top.store(new Node());
           seq = sharedSeq;
        }

        void push(std::string value) {
            TNode<std::string>* t;

            TNode<std::string>* n = new TNode<std::string>(value);
            while(true) {
                t = top;
                n->next = top.load();
                if(top.compare_exchange_strong(t, n)) {
                    sz.store(sz + 1);
                    return;
                }
                    
            }
        }

        std::string pop() {
            TNode<std::string>* t;
            int ret;

            while(true) {
                t = top;
                if(t == NULL) 
                    return "*"; // Since the test values are all greater than 1
                
                if(top.compare_exchange_strong(t, t->next)) {
                    sz.store(sz - 1);
                    return t->value;
                }
                    
            }
        }

        int size() {
            return sz;
        }

        //////////////////////////////////////////

        void push(std::string value, int threadId) {
            TNode<std::string>* t;
            TNode<std::string>* n = new TNode<std::string>(value);

            while(true) {
                t = top;
                n->next = top.load();
                if(top.compare_exchange_strong(t, n)) {
                    mtx.lock();
                    seq.push_back({threadId, {StackPair::push, value,""}});
                    mtx.unlock();
                    sz.store(sz + 1);
                    return;
                }
                    
            }
        }

        std::string pop(int threadId) {
            TNode<std::string>* t;
            int ret;

            while(true) {
                t = top;
                if(t == NULL) {
                    mtx.lock();
                    seq.push_back({threadId, {StackPair::push, "", "*"}});
                    mtx.unlock();
                    return "*"; // Since the test values are all greater than 1
                }
                    
                
                if(top.compare_exchange_strong(t, t->next)) {
                    mtx.lock();
                    seq.push_back({threadId, {StackPair::pop, "", t->value}});
                    mtx.unlock();
                    sz.store(sz - 1);
                    return t->value;
                }
                    
            }
        }

        int size(int threadId) {
            int size = sz;
            mtx.lock();
            seq.push_back({threadId, StackOperation(StackPair::size, "", std::to_string(size))});
            mtx.unlock();
            return size;
        }

};