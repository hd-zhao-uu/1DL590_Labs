#include <Node.h>
#include <limits>

class OptimisticList {
   private:
    Node* head = new Node(std::numeric_limits<int>::min());
    Node* tail = new Node(std::numeric_limits<int>::max());

    bool validate(Node* pre, Node* cur) {
        Node* node;

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
        Node *pre, *cur;
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
                    Node* node = new Node(value);
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
        Node *pre, *cur;

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
        Node *pre, *cur;
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