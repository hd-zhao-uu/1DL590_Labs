#include <thread>
#include <vector>
#include <Pair.h>
#include <array>
#include "Lists/CoarseList.cpp"
#include "Lists/FineList.cpp"
#include "Lists/OptimisticList.cpp"

template <class T>
void workerFunc(int id, T* set, std::vector<Pair>& testCase, int* counter) {
    for (auto it = testCase.begin(); it != testCase.end(); ++it) {
        // Do the operation from the test case
        switch (it->method) {
            case add:
                ret = set->add(it->input);
                counter[id] ++; // only add its own counter field
                break;
            case rmv:
                ret = set->rmv(it->input);
                counter[id] ++;
                break;
            case ctn:
                ret = set->ctn(it->input);
                counter[id] ++;
                break;
            default:
                printf("Worker %d no matching method found. \n", threadId);
        }
    }

    printf("Worker %d completed. \n", threadId);
}

int main() {



}


void task3() {
    std::vector<int> threadNums({2,4,8,16,32});




}

void task3_1(std::vector<int>& threadNums) {
    // input values: {0,1,...,7}

    for(auto& nThread:threadNums) {
        std::thread* workers = new std::thread[nThread];
        int* counter = new int[nThread];
        CoarseList* cl = new CoarseList();
        std::vector<Pair> testCase;

        for (int i = 0; i < nThread; i++) {
            workers[i] = std::thread(workerFunc<CoarseList>, i, std::ref(cl), std::ref(testCase), counter);
        }

        for (int i = 0; i < nThread; i++) {
            workers[i].join();
        }
    }

    for(auto& nThread:threadNums) {
        std::thread* workers = new std::thread[nThread];
        int* counter = new int[nThread];
        FineList* fl = new FineList();
        std::vector<Pair> testCase;

        for (int i = 0; i < nThread; i++) {
            workers[i] = std::thread(workerFunc<FineList>, i, std::ref(fl), std::ref(testCase), counter);
        }

        for (int i = 0; i < nThread; i++) {
            workers[i].join();
        }
    }

    for(auto& nThread:threadNums) {
        std::thread* workers = new std::thread[nThread];
        int* counter = new int[nThread];
        OptimisticList* ol = new OptimisticList();
        std::vector<Pair> testCase;

        for (int i = 0; i < nThread; i++) {
            workers[i] = std::thread(workerFunc<OptimisticList>, i, std::ref(ol), std::ref(testCase), counter);
        }

        for (int i = 0; i < nThread; i++) {
            workers[i].join();
        }
    }



}

void task3_2() {}

void task3_3() {}


int addAll(int* counter, int nThread) {
    int total = 0;

    for(int i = 0; i < nThread; i++) 
        total += counter[i];

    return total;
}