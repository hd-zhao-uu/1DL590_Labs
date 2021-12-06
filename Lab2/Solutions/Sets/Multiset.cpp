#include <iostream>
#include <limits>
#include <vector>
#include "Node.h"
#include "Operation.h"
#include <mutex>

class Multiset {
   private:
    Node* head = new Node(std::numeric_limits<int>::min());
    Node* tail = new Node(std::numeric_limits<int>::max());
    std::vector<std::pair<int, Operation>> seq;
    std::mutex mtx; // Only for vector<Operation> sharedSeq

   public:
    Multiset() { head->next = tail; }

    Multiset(std::vector<std::pair<int, Operation>>& sharedSeq) { 
        head->next = tail; 
        seq = sharedSeq;
    }

    ~Multiset() {
        Node* node = NULL;

        while (node != tail) {
            node = head->next;
            delete head;
            head = node;
        }

        delete tail;
    }

    bool add(int value) {
        /*
            Adds element `value` to the set and returns true
        */
        Node *pre, *cur;
        bool ret;

        head->lock.lock();
        pre = head;
        cur = pre->next;
        cur->lock.lock();

        while (cur->value < value) {
            pre->lock.unlock();
            pre = cur;
            cur = cur->next;
            cur->lock.lock();
        }

        Node* node = new Node(value);
        node->next = cur;
        pre->next = node;
        ret = true;

        cur->lock.unlock();
        pre->lock.unlock();
        return ret;
    }

    bool rmv(int value) {
        /*
            If possible, removes (an instance of) element `value` from the set
            and returns true, otherwise false
        */
        Node *pre, *cur;
        bool ret;

        head->lock.lock();
        pre = head;
        cur = pre->next;
        cur->lock.lock();

        while (cur->value < value) {
            pre->lock.unlock();
            pre = cur;
            cur = cur->next;
            cur->lock.lock();
        }

        if (cur->value == value) {
            pre->next = cur->next;
            ret = true;
        } else
            ret = false;

        cur->lock.unlock();
        pre->lock.unlock();
        return ret;
    }

    int ctn(int value) {
        /*
            Returns the multiplicity of element `value`(how many instances of
           `value` there are in the multiset)
        */
        Node *pre, *cur;

        head->lock.lock();
        pre = head;
        cur = pre->next;
        cur->lock.lock();

        while (cur->value < value) {
            pre->lock.unlock();
            pre = cur;
            cur = cur->next;
            cur->lock.lock();
        }

        Node* tCur = cur;  // record current ptr
        int ctn = 0;

        while (tCur->value == value) {
            ctn++;
            tCur = tCur->next;
        }

        cur->lock.unlock();
        pre->lock.unlock();
        return ctn;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    bool add(int value, int threadId) {
        Node *pre, *cur;
        bool ret;
        int retValue;
        
        head->lock.lock();
        pre = head;
        cur = pre->next;
        cur->lock.lock();

        while (cur->value < value) {
            pre->lock.unlock();
            pre = cur;
            cur = cur->next;
            cur->lock.lock();
        }

        Node* node = new Node(value);
        node->next = cur;
        pre->next = node;
        ret = true;

        retValue = ret ? 1 : 0; // true: 1, false: 0

        mtx.lock();
        seq.push_back({threadId, Operation{methodname::add, value, retValue}});
        mtx.unlock();

        cur->lock.unlock();
        pre->lock.unlock();
        return ret;
    }

    bool rmv(int value, int threadId) {
        Node *pre, *cur;
        bool ret;
        int retValue;

        head->lock.lock();
        pre = head;
        cur = pre->next;
        cur->lock.lock();

        while (cur->value < value) {
            pre->lock.unlock();
            pre = cur;
            cur = cur->next;
            cur->lock.lock();
        }

        if (cur->value == value) {
            pre->next = cur->next;
            ret = true;
        } else
            ret = false;

               
        retValue = ret ? 1 : 0; // true: 1, false: 0

        mtx.lock();
        seq.push_back({threadId, Operation{methodname::rmv, value, retValue}});
        mtx.unlock();

        cur->lock.unlock();
        pre->lock.unlock();

        return ret;
    }

    int ctn(int value, int threadId) {
        Node *pre, *cur;
        int count = 0;

        head->lock.lock();
        pre = head;
        cur = pre->next;
        cur->lock.lock();

        while (cur->value < value) {
            pre->lock.unlock();
            pre = cur;
            cur = cur->next;
            cur->lock.lock();
        }

        Node* tCur = cur;  // record current ptr
       
        while (cur->value == value) {
            count++;
            cur = cur->next;
        }

        mtx.lock();
        seq.push_back({threadId, Operation{methodname::ctn, value, count}});
        mtx.unlock();

        tCur->lock.unlock();
        pre->lock.unlock();
        return count;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////

    void printList() {
        Node* cur = head->next;
        std::cout << "[";
        while (cur != tail) {
            if (cur != head->next)
                std::cout << ", ";
            std::cout << cur->value;
            cur = cur->next;
        }
        std::cout << "]" << std::endl;
    }
};
