#include <Node.h>

class OptimisticList {
    Node<int>* head = new Node<int>(std::numeric_limits<int>::min());
    Node<int>* tail = new Node<int>(std::numeric_limits<int>::max());

   private:
    bool validate(Node<int>* pre, Node<int>* cur) {
        Node<int>* node;

        node = head;

        while (node->value < pre->value) {
            node = node->next;
        }

        if (node == pre && node->next == cur)
            return true;
        else
            return false;
    }

   public:
    OptimisticList() { head->next = tail; }

    bool add(int value) {
        Node<int>*pre, *cur;
        bool ret;

        while (true) {
            pre = head;
            cur = pre->next;

            while (cur->value < value) {
                pre = cur;
                cur = cur->next;
            }

            pre->lock.lock();
            cur->lock.lock();

            if (validate(pre, cur)) {
                if (cur->value == value)
                    ret = false;
                else {
                    Node<int>* node = new Node<int>(value);
                    node->next = cur;
                    pre->next = node;
                    ret = true;
                }

                pre->lock.unlock();
                cur->lock.unlock();
                return ret;
            } else {
                pre->lock.unlock();
                cur->lock.unlock();
            }
        }
    }

    bool rmv(int value) {
        bool ret;
        Node<int>*pre, *cur;

        while (true) {
            pre = head;
            cur = pre->next;

            while (cur->value < value) {
                pre = cur;
                cur = cur->next;
            }

            pre->lock.lock();
            cur->lock.lock();

            if (validate(pre, cur)) {
                if (cur->value == value) {
                    pre->next = cur->next;
                    ret = true;
                } else
                    ret = false;

                pre->lock.unlock();
                cur->lock.unlock();
                return ret;

            } else {
                pre->lock.unlock();
                cur->lock.unlock();
            }
        }
    }

    bool ctn(int value) {
        Node<int>*pre, *cur;
        bool ret;

        while (true) {
            pre = head;
            cur = pre->next;

            while (cur->value < value) {
                pre = cur;
                cur = cur->next;
            }

            pre->lock.lock();
            cur->lock.lock();

            if (validate(pre, cur)) {
                if (cur->value == value)
                    ret = true;
                else
                    ret = false;

                pre->lock.unlock();
                cur->lock.unlock();
                return ret;

            } else {
                pre->lock.unlock();
                cur->lock.unlock();
            }
        }
    }
};