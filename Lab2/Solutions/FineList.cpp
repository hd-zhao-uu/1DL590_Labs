#include <Node.h>
#include <limits>

class FineList {
    Node<int>* head = new Node<int>(std::numeric_limits<int>::min());
    Node<int>* tail = new Node<int>(std::numeric_limits<int>::max());

   public:
    FineList() { head->next = tail; }

    bool add(int value) {
        Node<int>*pre, *cur;

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

        if (cur->value == value)
            return false;

        else {
            Node<int>* node = new Node<int>(value);
            node->next = cur;
            pre->next = node;
            return true;
        }

        cur->lock.unlock();
        pre->lock.unlock();
    }

    bool rmv(int value) {
        Node<int>*pre, *cur;

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
            return true;
        } else
            return false;

        cur->lock.unlock();
        pre->lock.unlock();
    }

    bool ctn(int value) {
        Node<int>*pre, *cur;

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

        if (cur->value == value)
            return true;
        else
            return false;

        cur->lock.unlock();
        pre->lock.unlock();
    }
};