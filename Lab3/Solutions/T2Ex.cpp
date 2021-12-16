//  Compile: g++ T2Ex.cpp -lpthread -o t2.out

#include <array>
#include <fstream>
#include <thread>
#include <vector>

#include "Datastructures/LazyList.cpp"
#include "Datastructures/OptimisticList.cpp"
#include "Datastructures/Pair.h"
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

void _task1(std::vector<int>& threadNums,
            std::vector<Pair>& testCase,
            std::string& outpuFilePath,
            std::string& logPath);

int main() {
    std::vector<int> threadNums({2, 4, 8, 16, 32, 64});
    std::vector<Pair> testCase;
    int testSize = 100000;

    std::string outputFilePath = "./Results/T1_Results.txt";
    std::ofstream testFile(outputFilePath);

    std::string logPath = "./Results/data.txt";
    std::ofstream logFile(logPath);

    std::string bigDivider =
        "======================================================================"
        "================\n";
    std::string note;

    // Task 1-1
    // loadPairsFromFile("T3TEST_1.txt", testCase);
    note = "Test Value Range: [0, 7]. \n";
    std::cout << bigDivider;
    std::cout << note;

    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    strLine2File(logPath, bigDivider);
    strLine2File(logPath, note);
    createTestCases(0, 7, testSize, testCase);
    _task1(threadNums, testCase, outputFilePath, logPath);

    // Task 1-2
    note = "Test Value Range: [0, 1023]. \n";
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    strLine2File(logPath, bigDivider);
    strLine2File(logPath, note);
    createTestCases(0, 1023, testSize, testCase);
    _task1(threadNums, testCase, outputFilePath, logPath);

    int i;
    // Task 1-3
    note = "SET i = 10, values: [0...7]\n";
    i = 10;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    strLine2File(logPath, bigDivider);
    strLine2File(logPath, note);
    createTestCases(0, 7, testSize, i, testCase);
    _task1(threadNums, testCase, outputFilePath, logPath);

    note = "SET i = 10, values: [0...1023]\n";
    i = 10;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    strLine2File(logPath, bigDivider);
    strLine2File(logPath, note);
    createTestCases(0, 1023, testSize, i, testCase);
    _task1(threadNums, testCase, outputFilePath, logPath);

    note = "SET i = 50, values: [0...7]\n";
    i = 50;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    strLine2File(logPath, bigDivider);
    strLine2File(logPath, note);
    createTestCases(0, 7, testSize, i, testCase);
    _task1(threadNums, testCase, outputFilePath, logPath);

    note = "SET i = 50, values: [0...1023]\n";
    i = 50;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    strLine2File(logPath, bigDivider);
    strLine2File(logPath, note);
    createTestCases(0, 1023, testSize, i, testCase);
    _task1(threadNums, testCase, outputFilePath, logPath);

    note = "SET i = 90, values: [0...7]\n";
    i = 90;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    createTestCases(0, 7, testSize, i, testCase);
    _task1(threadNums, testCase, outputFilePath, logPath);

    note = "SET i = 90, values: [0...1023]\n";
    i = 90;
    std::cout << bigDivider;
    std::cout << note;
    strLine2File(outputFilePath, bigDivider);
    strLine2File(outputFilePath, note);
    strLine2File(logPath, bigDivider);
    strLine2File(logPath, note);
    createTestCases(0, 1023, testSize, i, testCase);
    _task1(threadNums, testCase, outputFilePath, logPath);
}

void _task1(std::vector<int>& threadNums,
            std::vector<Pair>& testCase,
            std::string& outputFilePath,
            std::string& logPath) {
    // input values: {0,1,...,7}
    std::string smallDivider =
        "----------------------------------------------------------------------"
        "----------------\n";
    std::string mark;

    double startTime, endTime, elapsed, opPer10Sec;
    std::vector<std::string> results;
    std::vector<std::string> logs;

    // Optimistic List Set
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
        opPer10Sec = testCase.size() * nThread / elapsed * 10;

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

        char logBuff[100];
        snprintf(logBuff, sizeof(logBuff), "%2d, %12.3lf\n", nThread,
                 opPer10Sec);
        std::string log = logBuff;
        logs.push_back(log);

        delete[] workers;
        delete ol;
    }

    resultVector2File(outputFilePath, results);
    results.clear();
    std::cout << smallDivider;
    strLine2File(outputFilePath, smallDivider);

    mark = "[Optimistic List Set]\n";
    strLine2File(logPath, mark);
    resultVector2File(logPath, logs);
    strLine2File(logPath, smallDivider);
    logs.clear();

    // Lazy List Set
    for (auto& nThread : threadNums) {
        GET_TIME(startTime);
        std::thread* workers = new std::thread[nThread];
        // int* counter = new int[nThread];
        LazyList* ll = new LazyList();

        for (int i = 0; i < nThread; i++) {
            workers[i] = std::thread(workerFunc<LazyList>, i, std::ref(ll),
                                     std::ref(testCase));
        }

        for (int i = 0; i < nThread; i++) {
            workers[i].join();
        }

        GET_TIME(endTime);
        elapsed = endTime - startTime;
        opPer10Sec = testCase.size() * nThread / elapsed * 10;

        char buff[100];
        snprintf(
            buff, sizeof(buff),
            "[OUTPUT] %2d threads, %24s: %12.3lf operations per 10 seconds.\n",
            nThread, "Lazy List Set", opPer10Sec);
        std::string result = buff;
        results.push_back(result);

        char logBuff[100];
        snprintf(logBuff, sizeof(logBuff), "%2d, %12.3lf\n", nThread,
                 opPer10Sec);
        std::string log = logBuff;
        logs.push_back(log);

        printf(
            "[OUTPUT] %2d threads, %24s: %12.3lf operations per 10 seconds.\n",
            nThread, "Lazy List Set", opPer10Sec);

        delete[] workers;
        delete ll;
    }

    resultVector2File(outputFilePath, results);
    results.clear();
    std::cout << smallDivider;
    strLine2File(outputFilePath, smallDivider);

    mark = "[Lazy List Set]\n";
    strLine2File(logPath, mark);
    resultVector2File(logPath, logs);
    strLine2File(logPath, smallDivider);
    logs.clear();
}
