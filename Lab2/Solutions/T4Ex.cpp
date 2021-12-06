//  Compile: g++ T4Ex.cpp -lpthread -o t4.out

#include <cstdio>
#include <set>
#include <thread>
#include "Sets/Multiset.cpp"
#include "Sets/Operation.h"
#include "Sets/Pair.h"
#include "Utilities/Testcases.cpp"

template <class T>
void workerFunc(int id,
                T* set,
                std::vector<Pair>& testCase) {
    bool ret;
    for (auto it = testCase.begin(); it != testCase.end(); ++it) {
        // Do the operation from the test case
        switch (it->method) {
            case add:
                set->add(it->input, id);
                // set->add(it->input);
                // printf("[thread %2d] add(%d)\n", id, it->input);
                break;
            case rmv:
                set->rmv(it->input, id);
                set->rmv(it->input);
                // printf("[thread %2d] rmv(%d)\n", id, it->input);
                break;
            case ctn:
                set->ctn(it->input, id);
                set->ctn(it->input);
                // printf("[thread %2d] ctn(%d)\n", id, it->input);
                break;
            default:
                printf("Worker %2d no matching method found. \n", id);
        }
    }

    printf("[DEBUG] Worker %d completed. \n", id);
}

void monitorFunc(std::vector<std::pair<int, Operation>>& sharedSeq) {
    // Pick the first operation from the sequence.
    // Check the element that you picked

    std::multiset<int> ms;
    int errorCtn = 0;

    for (auto& p : sharedSeq) {
        bool result = false;
        std::string mName;
        std::multiset<int>::iterator itFind, itRmv;
        int id = p.first;
        Operation op = p.second;
        
        switch (op.method) {
            case add: 
                printf("add!");
                ms.insert(op.input);
                mName = "add";
                result = true;
                break;
            case rmv: 
                printf("rmv!");
                itFind = ms.find(op.input);
                itRmv = ms.erase(itFind);
                mName = "rmv";
                if ( (itFind != ms.end()) == op.output)
                    result = true;
                else
                    result = false;
                break;
            case ctn: 
                printf("ctn!");
                int c = ms.count(op.input);
                if (c == op.output)
                    result = true;
                else
                    result = false;
                mName = "ctn";
                break;
        }
        if (!result && (op.method == add || op.method == rmv)) {
            printf("\t[ERROR] Opertion: (%s, %d, %s)\n", mName.c_str(),
                   op.input, op.output ? "true" : "false");
            errorCtn++;
        }else if(!result && op.method == ctn){
            printf("\t[ERROR] Opertion: (%s, %d, %d)\n", mName.c_str(),
                   op.input, op.output);
            errorCtn++;
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

    std::vector<Pair> testCase;
    std::vector<std::pair<int, Operation>> sharedSeq;

    Multiset* ms = new Multiset(sharedSeq);
    createTestCases(0, 500, opSize, testCase);

    std::thread* workers = new std::thread[nThread];

    for (int i = 0; i < nThread; i++) {
        workers[i] = std::thread(workerFunc<Multiset>, i, ms, std::ref(testCase));
    }

    for (int i = 0; i < nThread; i++) {
        workers[i].join();
    }

    
    delete[] workers;
    delete ms;

    std::thread monitor = std::thread(monitorFunc, std::ref(sharedSeq));
    monitor.join();
   
    return 0;
}
