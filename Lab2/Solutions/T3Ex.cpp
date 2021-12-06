//  Compile: g++ T3Ex.cpp -lpthread -o t3.out

#include <array>
#include <fstream>
#include <thread>
#include <vector>

#include "Sets/CoarseList.cpp"
#include "Sets/FineList.cpp"
#include "Sets/OptimisticList.cpp"
#include "Sets/Pair.h"
#include "Utilities/IO.cpp"
#include "Utilities/Testcases.cpp"
#include "Utilities/Timer.h"

template <class T>
void workerFunc(int id, T* set, std::vector<Pair>& testCase) {
    bool ret;
    for (auto it = testCase.begin(); it != testCase.end(); ++it) {
        // Do the operation from the test case
        switch (it->method) {
            case add:
                ret = set->add(it->input);
                // counter[id] ++; // only add its own counter field
                break;
            case rmv:
                ret = set->rmv(it->input);
                // counter[id] ++;
                break;
            case ctn:
                ret = set->ctn(it->input);
                // counter[id] ++;
                break;
            default:
                printf("Worker %d no matching method found. \n", id);
        }
    }

    // printf("Worker %d completed. \n", id);
}

void task3();
void _task3(std::vector<int>& threadNums,
            std::vector<Pair>& testCase,
            std::string& outpuFilePath);

int main() {
    task3();
}

void task3() {
    std::vector<int> threadNums({2, 4, 8, 16, 32});
    std::vector<Pair> testCase;
    int testSize = 100000;

    std::string outputFilePath = "./Results/T3_Results.txt";
    std::ofstream testFile(outputFilePath);

    std::string bigDivider =
        "======================================================================"
        "================\n";
    std::string note;

    // // Task 3-1
    // // loadPairsFromFile("T3TEST_1.txt", testCase);
    // note = "Test Value Range: [0, 7]. \n";
    // std::cout << bigDivider;
    // std::cout << note;

    // strLine2File(outputFilePath, bigDivider);
    // strLine2File(outputFilePath, note);
    // createTestCases(0, 7, testSize, testCase);
    // _task3(threadNums, testCase, outputFilePath);

    // // Task 3-2
    // note = "Test Value Range: [0, 1023]. \n";
    // std::cout << bigDivider;
    // std::cout << note;
    // strLine2File(outputFilePath, bigDivider);
    // strLine2File(outputFilePath, note);
    // createTestCases(0, 1023, testSize, testCase);
    // _task3(threadNums, testCase, outputFilePath);

    int i;
    // Task 3-3
    note = "SET i = 10, values: [0...7]\n";
    i = 10;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    createTestCases(0, 7, testSize, i, testCase);
    _task3(threadNums, testCase, outputFilePath);

    note = "SET i = 10, values: [0...1023]\n";
    i = 10;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    createTestCases(0, 1023, testSize, i, testCase);
    _task3(threadNums, testCase, outputFilePath);

    note = "SET i = 50, values: [0...7]\n";
    i = 50;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    createTestCases(0, 7, testSize, i, testCase);
    _task3(threadNums, testCase, outputFilePath);

    note = "SET i = 50, values: [0...1023]\n";
    i = 50;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    createTestCases(0, 1023, testSize, i, testCase);
    _task3(threadNums, testCase, outputFilePath);

    note = "SET i = 90, values: [0...7]\n";
    i = 90;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    createTestCases(0, 7, testSize, i, testCase);
    _task3(threadNums, testCase, outputFilePath);

     note = "SET i = 90, values: [0...1023]\n";
    i = 90;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    createTestCases(0, 1023, testSize, i, testCase);
    _task3(threadNums, testCase, outputFilePath);
}

void _task3(std::vector<int>& threadNums,
            std::vector<Pair>& testCase,
            std::string& outputFilePath) {
    // input values: {0,1,...,7}
    std::string smallDivider =
        "----------------------------------------------------------------------"
        "----------------\n";
    double startTime, endTime, elapsed, opPer10Sec;
    std::vector<std::string> results;

    // Coarse-grained List Set
    for (auto& nThread : threadNums) {
        GET_TIME(startTime);
        std::thread* workers = new std::thread[nThread];
        // int* counter = new int[nThread];
        CoarseList* cl = new CoarseList();

        for (int i = 0; i < nThread; i++) {
            workers[i] = std::thread(workerFunc<CoarseList>, i, std::ref(cl),
                                     std::ref(testCase));
        }

        for (int i = 0; i < nThread; i++) {
            workers[i].join();
        }

        GET_TIME(endTime);
        elapsed = endTime - startTime;
        opPer10Sec = testCase.size() / elapsed * 10;

        char buff[100];
        snprintf(
            buff, sizeof(buff),
            "[OUTPUT] %2d threads, %24s: %12.3lf operations per 10 seconds.\n",
            nThread, "Coarse-grained List Set", opPer10Sec);
        std::string result = buff;
        results.push_back(result);

        printf(
            "[OUTPUT] %2d threads, %24s: %12.3lf operations per 10 seconds.\n",
            nThread, "Coarse-grained List Set", opPer10Sec);

        delete[] workers;
        delete cl;
    }

    resultVector2File(outputFilePath, results);
    results.clear();
    std::cout << smallDivider;
    strLine2File(outputFilePath, smallDivider);

    // Coarse-grained List Set
    for (auto& nThread : threadNums) {
        GET_TIME(startTime);
        std::thread* workers = new std::thread[nThread];
        // int* counter = new int[nThread];
        FineList* fl = new FineList();

        for (int i = 0; i < nThread; i++) {
            workers[i] = std::thread(workerFunc<FineList>, i, std::ref(fl),
                                     std::ref(testCase));
        }

        for (int i = 0; i < nThread; i++) {
            workers[i].join();
        }

        GET_TIME(endTime);
        elapsed = endTime - startTime;
        opPer10Sec = testCase.size() / elapsed * 10;

        char buff[100];
        snprintf(
            buff, sizeof(buff),
            "[OUTPUT] %2d threads, %24s: %12.3lf operations per 10 seconds.\n",
            nThread, "Fine-grained List Set", opPer10Sec);
        std::string result = buff;
        results.push_back(result);
        printf(
            "[OUTPUT] %2d threads, %24s: %12.3lf operations per 10 seconds.\n",
            nThread, "Fine-grained List Set", opPer10Sec);

        delete[] workers;
        delete fl;
    }

    resultVector2File(outputFilePath, results);
    results.clear();
    std::cout << smallDivider;
    strLine2File(outputFilePath, smallDivider);

    // Coarse-grained List Set
    for (auto& nThread : threadNums) {
        GET_TIME(startTime);
        std::thread* workers = new std::thread[nThread];
        int* counter = new int[nThread];
        OptimisticList* ol = new OptimisticList();

        for (int i = 0; i < nThread; i++) {
            workers[i] = std::thread(workerFunc<OptimisticList>, i,
                                     std::ref(ol), std::ref(testCase));
        }

        for (int i = 0; i < nThread; i++) {
            workers[i].join();
        }

        GET_TIME(endTime);
        elapsed = endTime - startTime;
        opPer10Sec = testCase.size() / elapsed * 10;

        char buff[100];
        snprintf(
            buff, sizeof(buff),
            "[OUTPUT] %2d threads, %24s: %12.3lf operations per 10 seconds.\n",
            nThread, "Optimistic List Set", opPer10Sec);
        std::string result = buff;
        results.push_back(result);
        printf(
            "[OUTPUT] %2d threads, %24s: %12.3lf operations per 10 seconds.\n",
            nThread, "Optimistic List Set", opPer10Sec);

        delete[] workers;
        delete ol;
    }

    resultVector2File(outputFilePath, results);
    results.clear();
    std::cout << smallDivider;
    strLine2File(outputFilePath, smallDivider);
}
