#include <iostream>
#include <set>

class SetLib {
   public:
        bool add(int item, bool r) {
            // cheak if the item is in the set.
            std::set<int>::iterator it = state.find(item);
            // if the item is in the set, and the input r is true,
            // illegal operation.
            if ((it != state.end()) && r)
                return false;

            // if the item is not in the set, and the input r is false,
            // illegal operation.
            if ((it == state.end()) && !r)
                return false;

            // the item is not in the set, add.
            std::pair<std::set<int>::iterator, bool> ret = state.insert(item);

            return true;
        }

        bool rmv(int item, bool r) {
            // cheak if the item is in the set.
            std::set<int>::iterator it = state.find(item);
            // if the item is in the set, and the input r is false,
            // illegal operation.
            if ((it != state.end()) && !r)
                return false;

            // if the item is not in the set, and the input r is true,
            // illegal operation.
            if ((it == state.end()) && r)
                return false;

            int size = state.erase(item);
            // size == 0 and rmv false; size != 0 and rmv true
            // if (((size != 0) && r) || (size == 0) && !r)
            return true;
        }

        bool ctn(int item, bool r) {
            std::set<int>::iterator it = state.find(item);
            if ((it != state.end()) == r)
                return true;
            return false;
        }

        // Add your own member functions if needed
        void printSet() {
            std::cout << "\t[";
            for (auto it = state.begin(); it != state.end(); it++) {
                if (it != state.begin())
                    std::cout << ", ";
                std::cout << *it;
            }
            std::cout << "]" << std::endl;
        }

   private:
        std::set<int> state;
};
