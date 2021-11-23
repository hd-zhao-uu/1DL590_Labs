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
#include "CoarseSet.cpp"



using namespace std;

std::vector<std::pair<int, operation>> sharedSeq;

template <class T>
void worker_func(int threadId, T* set, std::vector<operation> testCase) {
    bool ret;
    for (auto it = testCase.begin(); it != testCase.end(); ++it) {
        // Do the operation from the test case
        switch (it->method) {
            case add:
                ret = set->add(it->input);
                break;
            case rmv:
                ret = set->rmv(it->input);
                break;
            case ctn:
                ret = set->ctn(it->input);
                break;
            default:
                printf( "Worker %d no matching method found. \n", threadId);
        }
        sharedSeq.push_back(
            {threadId, operation{it->method, it->input, ret}});
    }

    printf("Worker %d completed. \n", threadId);
}

template <class T>
void worker_func2(int threadId, T* set, std::vector<operation> testCase) {
    bool ret;
    for (auto it = testCase.begin(); it != testCase.end(); ++it) {
        // Do the operation from the test case
        switch (it->method) {
            case add:
                set->add(it->input, threadId);
                break;
            case rmv:
                ret = set->rmv(it->input, threadId);
                break;
            case ctn:
                ret = set->ctn(it->input, threadId);
                break;
            default:
                printf( "Worker %d no matching method found. \n", threadId);
        }
    }
    printf("Worker %d completed. \n", threadId);
}


void monitor_func(int nThread) {
    // Pick the first operation from the sequence.
    // Check the element that you picked
    SetLib sl;
    int errorCtn = 0;
    for (auto oPair : sharedSeq) {
        int threadId = oPair.first;
        operation op = oPair.second;
        bool ret;
        std::string mName;
        switch (op.method) {
            case add:
                ret = sl.add(op.input, op.output);
                mName = "add";
                break;
            case rmv:
                ret = sl.rmv(op.input, op.output);
                mName = "rmv";
                break;
            case ctn:
                ret = sl.ctn(op.input, op.output);
                mName = "ctn";
                break;
        }
        if (!ret) {
            printf("\t[ERROR] Thread Id = %d, Opertion: (%s, %d, %s)\n", threadId,
                   mName.c_str(), op.input, op.output ? "true" : "false");
            errorCtn++;
        }
    }

    if(errorCtn == 0) {
        printf("\nNO ERROR OPERATION!\n\n");
    }

    printf("Monitor completed\n");
}

/*
    Start Tasks
*/
void task1() {
    // test task 1
    std::cout << "------------- START TEST TASK 1 -------------" << std::endl;
    std::vector<operation> testOps;
    loadOperationsFromFile("./testcases/T1TEST.txt", testOps);

    std::cout << testOps.size() << " test Operations. Index starts from 1."
              << std::endl;
    testOperations(testOps);
    std::cout << "------------- TASK 1 ENDS -------------\n" << std::endl;
}

void task2() {
    std::cout << "------------- START TEST TASK 2 -------------" << std::endl;
    // init pairs
    std::vector<std::pair<methodname, int>> testPairs;
    std::vector<operation> testOps;
    string testfile = "./testcases/T2TEST.txt";
    loadPairsFromFile(testfile, testPairs);

    // init operations;
    generateOperationsFromPairs(testPairs, testOps);
    std::cout << "Generate " << testOps.size()
              << " test operations. Index starts from 1." << std::endl;
    testOperations(testOps);
    std::cout << "------------- TASK 2 ENDS -------------\n" << std::endl;
}

void _task3(int testCaseN, int nThread) {
    std::thread* worker = new std::thread[nThread];
    SetList* set = new SetList();
    std::vector<operation> testCase;

    std::vector<std::pair<methodname, int>> testPairs;
    std:string testfile = "./testcases/T3TEST_" + to_string(testCaseN) + ".txt";
    loadPairsFromFile(testfile, testPairs);
    

    for (auto pair : testPairs)
        testCase.push_back(
            {pair.first, pair.second, false});  // set false as default

    
    // Run workers------------------
    for (int i = 0; i < nThread; i++) {
        
        worker[i] = thread(worker_func<SetList>, i, std::ref(set), testCase);
    }

    for (int i = 0; i < nThread; i++) {
        worker[i].join();
    }
    //------------------------------
    // Run monitor-------------------
    std::thread monitor = std::thread(monitor_func, nThread);
    monitor.join();
    //------------------------------
    delete set;
    sharedSeq.clear();
}

void task3() {
    std::cout << "------------- START TEST TASK 3 -------------" << std::endl;
    std::vector<int> threads({2,4,8});

    for(int nThread:threads) {
        printf("== Num of threads = %d  ==\n", nThread);
        for(int i = 0; i < 5; i++) {
            printf("\n{Test Case %d Starts} \n", i+1);
            _task3(i, nThread);
            printf("{Test Case %d Ends} \n\n", i+1);
        }
       
        
    } 

    sharedSeq.clear();
    std::cout << "------------- TASK 3 ENDS -------------\n" << std::endl;
}

// --------------------------------------------------------------------------------------
void _task4(int testCaseN, int nThread) {
    std::thread* worker = new std::thread[nThread];
    CoarseSet* set = new CoarseSet(sharedSeq);
    std::vector<operation> testCase;

    std::vector<std::pair<methodname, int>> testPairs;
    std:string testfile = "./testcases/T3TEST_" + to_string(testCaseN) + ".txt";
    loadPairsFromFile(testfile, testPairs);
    

    for (auto pair : testPairs)
        testCase.push_back(
            {pair.first, pair.second, false});  // set false as default

    
    // Run workers------------------
    for (int i = 0; i < nThread; i++) {
        
        worker[i] = thread(worker_func2<CoarseSet>, i, std::ref(set), testCase);
    }

    for (int i = 0; i < nThread; i++) {
        worker[i].join();
    }
    //------------------------------
    // Run monitor-------------------
    std::thread monitor = std::thread(monitor_func, nThread);
    monitor.join();
    //------------------------------
    delete set;
    sharedSeq.clear();
}

void task4() {
    std::cout << "------------- START TEST TASK 4 -------------" << std::endl;
    std::vector<int> threads({2,4,8});

    for(int nThread:threads) {
        printf("== Num of threads = %d  ==\n", nThread);
        for(int i = 0; i < 5; i++) {
            printf("\n {Test Case %d Starts} \n", i+1);
            _task4(i, nThread);
            printf("{Test Case %d Ends} \n\n", i+1);
        }  
    } 
    

    std::cout << "------------- TASK 4 ENDS -------------\n" << std::endl;
}

int main() {
    task1();
    task2();
    // task3();
    task4();
    return 0;
}
