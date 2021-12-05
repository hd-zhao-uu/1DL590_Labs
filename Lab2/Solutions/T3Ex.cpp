#include <thread>
#include <vector>
#include <array>

#include "Lists/Pair.h"
#include "Lists/CoarseList.cpp"
#include "Lists/FineList.cpp"
#include "Lists/OptimisticList.cpp"
#include "Utilities/Timer.h"
#include "Utilities/Testcases.cpp"

template <class T>
void workerFunc(int id, T* set, std::vector<Pair>& testCase, int* counter) {
    bool ret;
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
                printf("Worker %d no matching method found. \n", id);
        }
    }

    // printf("Worker %d completed. \n", id);
}

void task3();
void _task3(std::vector<int>& threadNums, std::vector<Pair>& testCase);



int main() {
    task3();


}


void task3() {
    std::vector<int> threadNums({2,4,8,16,32});
    std::vector<Pair> testCase;
    int testSize = 100000;

    // Task 3-1
    // loadPairsFromFile("T3TEST_1.txt", testCase);
    printf("===============================================================\n");
    printf("Test Value Range: [0, 7]. \n");
    createTestCases(0, 7, testSize, testCase);
    _task3(threadNums, testCase);

    // Task 3-2
    printf("===============================================================\n");
    printf("Test Value Range: [0, 1023]. \n");
    createTestCases(0, 1023, testSize, testCase);
    _task3(threadNums, testCase);

    // Task 3-3
    printf("===============================================================\n");
    printf("SET i = 60\n");
    createTestCases(0, 1023, 60, testSize, testCase);
    _task3(threadNums, testCase);



}

void _task3(std::vector<int>& threadNums, std::vector<Pair>& testCase) {
    // input values: {0,1,...,7}
    double startTime, endTime, elapsed, opPer10Sec;
    
    // Coarse-grained List Set
    for(auto& nThread:threadNums) {
        GET_TIME(startTime);
        std::thread* workers = new std::thread[nThread];
        int* counter = new int[nThread];
        CoarseList* cl = new CoarseList();
        
        for (int i = 0; i < nThread; i++) {
            workers[i] = std::thread(workerFunc<CoarseList>, i, std::ref(cl), std::ref(testCase), counter);
        }

        for (int i = 0; i < nThread; i++) {
            workers[i].join();
        }

        GET_TIME(endTime);
        elapsed = endTime - startTime;
        opPer10Sec = testCase.size() / elapsed * 10;

        printf("[OUTPUT] %d threads, %s: %.3lf operations per 10 seconds.\n", nThread, "Coarse-grained List Set", opPer10Sec);
        
    }
    printf("---------------------------------------------------------------------------------\n");
    
    // Coarse-grained List Set
    for(auto& nThread:threadNums) {
        GET_TIME(startTime);
        std::thread* workers = new std::thread[nThread];
        int* counter = new int[nThread];
        FineList* fl = new FineList();

        for (int i = 0; i < nThread; i++) {
            workers[i] = std::thread(workerFunc<FineList>, i, std::ref(fl), std::ref(testCase), counter);
        }

        for (int i = 0; i < nThread; i++) {
            workers[i].join();
        }

        GET_TIME(endTime);
        elapsed = endTime - startTime;
        opPer10Sec = testCase.size() / elapsed * 10;

        printf("[OUTPUT] %d threads, %s: %.3lf operations per 10 seconds.\n", nThread, "Fine-grained List Set", opPer10Sec);
        
    }
    printf("---------------------------------------------------------------------------------\n");

    // Coarse-grained List Set
    for(auto& nThread:threadNums) {
        GET_TIME(startTime);
        std::thread* workers = new std::thread[nThread];
        int* counter = new int[nThread];
        OptimisticList* ol = new OptimisticList();

        for (int i = 0; i < nThread; i++) {
            workers[i] = std::thread(workerFunc<OptimisticList>, i, std::ref(ol), std::ref(testCase), counter);
        }

        for (int i = 0; i < nThread; i++) {
            workers[i].join();
        }

        GET_TIME(endTime);
        elapsed = endTime - startTime;
        opPer10Sec = testCase.size() / elapsed * 10;

        printf("[OUTPUT] %d threads, %s: %.3lf operations per 10 seconds.\n", nThread, "Optimistic List Set", opPer10Sec);
        
    }
    printf("---------------------------------------------------------------------------------\n");
}

// void task3_3() {}


// int addAll(int* counter, int nThread) {
//     int total = 0;

//     for(int i = 0; i < nThread; i++) 
//         total += counter[i];

//     return total;
// }