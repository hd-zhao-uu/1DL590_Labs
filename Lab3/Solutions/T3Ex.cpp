//  Compile: g++ T3Ex.cpp -lpthread -o t3.out

#include <cstdio>
#include <set>
#include <thread>
#include <stack>
#include "Datastructures/TreiberStack.cpp"
#include "Datastructures/StackOperation.h"
#include "Datastructures/StackPair.h"
#include "Utilities/Testcases.cpp"

void workerFunc(int id,
                TreiberStack* stk,
                std::vector<StackPair::StackPair>& testCase) {
    bool ret;
    for (auto it = testCase.begin(); it != testCase.end(); ++it) {
        // Do the operation from the test case
        switch (it->method) {
            case StackPair::push:
                stk->push(it->input, id);
                break;
            case StackPair::pop:
                stk->pop(id);
                break;
            case StackPair::size:
                stk->size(id);
                break;
            default:
                printf("Worker %2d no matching method found. \n", id);
        }
    }

    printf("[DEBUG] Worker %d completed. \n", id);
}

void monitorFunc(std::vector<std::pair<int, StackOperation>>& sharedSeq) {
    // Pick the first operation from the sequence.
    // Check the element that you picked

    std::stack<std::string> stk;
    int errorCtn = 0;

    for (auto& p : sharedSeq) {
        bool result = false;
        std::string mName;
        int id;
        StackOperation op;
        std::tie(id, op) = p;

        std::string top;
        int size;
        switch (op.method) {
            case StackPair::push: 
                stk.push(op.input);
                break;
            case StackPair::pop: 
                top = stk.top();
                stk.pop();
                if(top != op.output) errorCtn++;
                break;
            case StackPair::size: 
                size = stk.size();
                if(op.output != std::to_string(size)) errorCtn++;
                break;
        }
        
    }

    if (errorCtn == 0) {
        printf("\n[OUTPUT] NO ERROR OPERATION!\n");
    } else {
        printf("[OUTPUT] Total Error Operations: %d\n", errorCtn);
    }
}

int main() {
    int nThread = 16;
    int opSize = 100;

    std::vector<StackPair::StackPair> testCase;
    std::vector<std::pair<int, StackOperation>> sharedSeq;

    TreiberStack* stk = new TreiberStack(sharedSeq);
    createTestCases(0, 500, opSize, testCase);

    std::thread* workers = new std::thread[nThread];

    for (int i = 0; i < nThread; i++) {
        workers[i] = std::thread(workerFunc, i, stk, std::ref(testCase));
    }

    for (int i = 0; i < nThread; i++) {
        workers[i].join();
    }

    delete[] workers;
    delete stk;

    std::thread monitor = std::thread(monitorFunc, std::ref(sharedSeq));
    monitor.join();
   
    return 0;
}
