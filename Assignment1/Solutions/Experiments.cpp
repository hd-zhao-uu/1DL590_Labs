/**** This is a helper/skeleton code for the assignment     ****/
/**** Author: Sarbojit Das                                  ****/
/**** Compile using command g++ helper_code.cpp -lpthread ****/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>
#include "LinearizedSeq.cpp"
#include "SetLib.cpp"
#include <fstream>
#include <sstream>
#include "SetList.cpp"

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
    cout << "Monitor completed" << endl;
}

void testOperations();

void task1() {
    // test task 1
    std::cout << "------------- START TEST TASK 1 -------------" << std::endl;

    string testfile = "./testcases/testops.txt";
    std::ifstream infile(testfile);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            string methodStr;
            int input;
            string outputStr;
            iss >> methodStr >> input >> outputStr;

            methodname method;
            if(methodStr == "add") 
                method = methodname::add;
            else if(methodStr == "rmv")
                method = methodname::rmv;
            else
                method = methodname::ctn;    
            
            bool output;
            output = outputStr == "true" ? true:false;
            // std::cout << methodStr <<", " << input << ", " << output << std::endl;
            Linearized_seq.push(operation{method, input, output});
        }
        infile.close();
    }

    
    std::cout << Linearized_seq.size() << " test Operations. Index starts from 1." << std::endl;

    testOperations();

    std::cout << "------------- TASK 1 ENDS -------------\n" << std::endl;
}


void task2() {
    std::cout << "------------- START TEST TASK 2 -------------" << std::endl;
    // init pairs
    std::vector<std::pair<methodname, int>> testPairs;
    string testfile = "./testcases/testpairs.txt";

    std::ifstream infile(testfile);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            string methodStr;
            int input;
            iss >> methodStr >> input;

            methodname method;
            if(methodStr == "add") 
                method = methodname::add;
            else if(methodStr == "rmv")
                method = methodname::rmv;
            else
                method = methodname::ctn;    
            // std::cout << methodStr <<", " << input << std::endl;
            testPairs.push_back({method, input});
        }
        infile.close();
    }
    std::cout << testPairs.size() << " test Pairs. Index starts from 1." << std::endl;

    // init operations;
    SetList setlist;
    bool ret;
    for(auto testPair: testPairs) {
        switch(testPair.first) {
            case add:
                ret = setlist.add(testPair.second);
                break;
            case rmv:
                ret = setlist.rmv(testPair.second);
                break;
            case ctn:
                ret = setlist.ctn(testPair.second);
                break;   
        }    
        Linearized_seq.push(operation{testPair.first, testPair.second, ret});
    }
    std::cout << "Generate " << Linearized_seq.size() << " test operations. Index starts from 1." << std::endl;
    testOperations();
    std::cout << "------------- TASK 2 ENDS -------------\n" << std::endl;
}

void task3() {
    int N_Threads = 3;
    thread* worker = new thread[N_Threads];
    // SetList *set = new SetList();
    // Run workers------------------
    for (int i = 0; i < N_Threads; i++) {
        vector<operation> test_case;
        // fill test_case with your sequence of operations
        // worker[i]=thread(worker_func<SetList>, i, ref(set), test_case);
    }

    for (int i = 0; i < N_Threads; i++) {
        // worker[i].join();
    }
    //------------------------------
    // Run monitor-------------------
    thread monitor = thread(monitor_func, N_Threads);
    monitor.join();
    //------------------------------
    // delete set;
}

void task4() {}

int main() {
    task1();
    task2();
    // task3();
    // task4();
    return 0;
}


/* Utilities */
void testOperations() {
    SetLib sl;
    std::vector<std::pair<int, operation>> errorOps;
    int i = 0;
    while(!Linearized_seq.empty()) {
        auto op = Linearized_seq.front();
        Linearized_seq.pop();
        bool ret;
        switch (op.method) {
            case add:
                printf("[OPERATION%3d] add(%d, %s)\n", i+1, op.input,
                       op.output ? "true" : "false");
                ret = sl.add(op.input, op.output);
                break;
            case rmv:
                printf("[OPERATION%3d] rmv(%d, %s)\n", i+1, op.input,
                       op.output ? "true" : "false");
                ret = sl.rmv(op.input, op.output);
                break;
            case ctn:
                printf("[OPERATION%3d] ctn(%d, %s)\n", i+1, op.input,
                       op.output ? "true" : "false");
                ret = sl.ctn(op.input, op.output);
                break;
        }
        if (!ret) {
            errorOps.push_back({i+1, op});
            std::cout << "!!ERROR OPERATION" << std::endl;
        }
        i++;
        
        std::cout << "CURRENT SET: " << std::endl;
        sl.printSet();
        std::cout << endl;
    }
    
    // clear queue
    std::queue<operation> empty;
    std::swap(Linearized_seq, empty);

    // print error ops
    std::cout << "ERROR OPERATIONS" << std::endl;
    if(errorOps.size()) {
        std::for_each(errorOps.begin(), errorOps.end(), [](auto p) {
            switch (p.second.method) {
                case add:
                    printf("[OPERATION%3d] add(%d, %s)\n", p.first, p.second.input, p.second.output ? "true" : "false");
                    break;
                case rmv:
                    printf("[OPERATION%3d] rmv(%d, %s)\n", p.first, p.second.input, p.second.output ? "true" : "false");
                    break;
                case ctn:
                    printf("[OPERATION%3d] ctn(%d, %s)\n", p.first, p.second.input, p.second.output ? "true" : "false");
                    break;
            }
        });
    }
    else
        std::cout << "\tNo Error Operation!" << std::endl;
}