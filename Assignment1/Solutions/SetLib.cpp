#include <iostream>
#include <set>

class SetLib {
   public:
    bool add(int item, bool r) {
        std::pair<std::set<int>::iterator, bool> ret = state.insert(item);
        if (ret.second != r)
            return false;
        return true;
    }

    bool rmv(int item, bool r) {
        int size = state.erase(item);
        if ((size != 0) == r)
            return true;
        return false;
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
