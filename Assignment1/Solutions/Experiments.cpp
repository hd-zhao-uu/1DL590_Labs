/**** This is a helper/skeleton code for the assignment     ****/
/**** Author: Sarbojit Das                                  ****/
/**** Compile using command g++ helper_code.cpp -lpthread ****/

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include "utilities.cpp"

using namespace std;

template <class T>
void worker_func(int thread_id, T* set, vector<operation> test_case) {
    for (auto it = test_case.begin(); it != test_case.end(); ++it) {
        // Do the operation from the test case
        switch (it->method) {
            case add:
                set->add(it->input);
                break;
            case rmv:
                set->rmv(it->input);
                break;
            case ctn:
                set->ctn(it->input);
                break;
            default:
                std::cout << "Worker " << thread_id
                          << " no matching method found" << std::endl;
        }
    }

    std::cout << "Worker " << thread_id << " completed" << endl;
}

void monitor_func(int N_Threads) {
    // Pick the first operation from the sequence.
    // Check the element that you picked
    SetLib sl;
    
    std::cout << "Monitor completed" << std::endl;
}


/*
    Start Tasks
*/
void task1() {
    // test task 1
    std::cout << "------------- START TEST TASK 1 -------------" << std::endl;
    std::vector<operation> testOps;
    loadOperationsFromFile("./testcases/testops.txt", testOps);

    std::cout << testOps.size()
              << " test Operations. Index starts from 1." << std::endl;
    testOperations(testOps);
    std::cout << "------------- TASK 1 ENDS -------------\n" << std::endl;
}

void task2() {
    std::cout << "------------- START TEST TASK 2 -------------" << std::endl;
    // init pairs
    std::vector<std::pair<methodname, int>> testPairs;
    std::vector<operation> testOps;
    string testfile = "./testcases/testpairs.txt";
    loadPairsFromFile("./testcases/testpairs.txt", testPairs);

    // init operations;
    generateOperationsFromPairs(testPairs, testOps);
    std::cout << "Generate " << testOps.size()
              << " test operations. Index starts from 1." << std::endl;
    testOperations(testOps);
    std::cout << "------------- TASK 2 ENDS -------------\n" << std::endl;
}

void task3() {
    int N_Threads = 3;
    thread* worker = new thread[N_Threads];
    SetList* set = new SetList();
    // Run workers------------------
    for (int i = 0; i < N_Threads; i++) {
        // fill test_case with your sequence of operations
        std::vector<operation> test_case;
        std::vector<std::pair<methodname, int>> testPairs;
        string testfile = "./testcases/testpairs.txt";
        loadPairsFromFile("./testcases/testpairs.txt", testPairs);
        generateOperationsFromPairs(testPairs, test_case);

        worker[i] = thread(worker_func<SetList>, i, std::ref(set), test_case);
    }

    for (int i = 0; i < N_Threads; i++) {
        worker[i].join();
    }
    //------------------------------
    // Run monitor-------------------
    thread monitor = thread(monitor_func, N_Threads);
    monitor.join();
    //------------------------------
    delete set;
}

void task4() {}

int main() {
    task1();
    task2();
    // task3();
    // task4();
    return 0;
}

