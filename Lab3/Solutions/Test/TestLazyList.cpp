//  Compile: g++ TestLazyList.cpp -lpthread -o tll.out

#include <cstdio>
#include <set>
#include <thread>
#include "../Datastructures/LazyList.cpp"
#include "../Datastructures/Operation.h"
#include "../Datastructures/Pair.h"
#include "../Datastructures/SetLib.cpp"
#include "../Utilities/Testcases.cpp"

template <class T>
void workerFunc(int id, T* set, std::vector<Pair>& testCase) {
    bool ret;
    for (auto it = testCase.begin(); it != testCase.end(); ++it) {
        // Do the operation from the test case
        switch (it->method) {
            case add:
                set->add(it->input, id);
                // printf("[thread %2d] add(%d)\n", id, it->input);
                break;
            case rmv:
                set->rmv(it->input, id);
                // printf("[thread %2d] rmv(%d)\n", id, it->input);
                break;
            case ctn:
                set->ctn(it->input, id);
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

    SetLib sl;
    int errorCtn = 0;
    for (auto oPair : sharedSeq) {
        int threadId = oPair.first;
        Operation op = oPair.second;
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
            printf("\t[ERROR] Thread Id = %d, Opertion: (%s, %d, %s)\n",
                   threadId, mName.c_str(), op.input,
                   op.output ? "true" : "false");
            errorCtn++;
        }
    }

    if (errorCtn == 0) {
        printf("\nNO ERROR OPERATION!\n\n");
    }

    printf("Monitor completed\n");
}

int main() {
    int nThread = 16;
    int opSize = 100;

    std::vector<Pair> testCase;
    std::vector<std::pair<int, Operation>> sharedSeq;

    LazyList* ll = new LazyList(sharedSeq);
    createTestCases(0, 500, opSize, testCase);

    std::thread* workers = new std::thread[nThread];

    for (int i = 0; i < nThread; i++) {
        workers[i] =
            std::thread(workerFunc<LazyList>, i, ll, std::ref(testCase));
    }

    for (int i = 0; i < nThread; i++) {
        workers[i].join();
    }

    delete[] workers;
    delete ll;

    std::thread monitor = std::thread(monitorFunc, std::ref(sharedSeq));
    monitor.join();

    return 0;
}
