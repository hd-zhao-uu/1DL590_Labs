#include <cstdio>
#include <thread>
#include <string>
#include "../Datastructures/TreiberStack.cpp"

int nThread = 10;

void func(int threadId, TreiberStack* ts) {
    ts->push(std::to_string(threadId * nThread + 0));
    ts->push(std::to_string(threadId * nThread + 1));
    ts->push(std::to_string(threadId * nThread + 2));
    ts->push(std::to_string(threadId * nThread + 3));
    
    printf("[%d] %s\n", threadId, ts->pop().c_str());
    printf("[%d] %s\n", threadId, ts->pop().c_str());
    printf("[%d] %s\n", threadId, ts->pop().c_str());
    printf("[%d] %s\n", threadId, ts->pop().c_str());
    printf("[%d] %s\n", threadId, ts->pop().c_str());
    printf("[%d] %s\n", threadId, ts->pop().c_str());
    printf("[%d] %s\n", threadId, ts->pop().c_str());
}

int main() {
    TreiberStack* ts = new TreiberStack();

    std::thread* workers = new std::thread[nThread];

    for (int i = 0; i < nThread; i++) {
        workers[i] = std::thread(func, i, ts);
    }

    for (int i = 0; i < nThread; i++) {
        workers[i].join();
    }

    delete[] workers;
    delete ts;

    return 0;
}