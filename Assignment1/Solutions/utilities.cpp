#include <vector>
#include "LinearizedSeq.cpp"
#include <string>
#include "SetList.cpp"
#include "SetLib.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

/* 
    Utilities 
*/
void generateOperationsFromPairs(
    std::vector<std::pair<methodname, int>> testPairs,
    std::vector<operation>& ops) {
    SetList setlist;
    bool ret;
    for (auto testPair : testPairs) {
        switch (testPair.first) {
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
        ops.push_back(operation{testPair.first, testPair.second, ret});
    }
}

void loadPairsFromFile(std::string testfile,
                       std::vector<std::pair<methodname, int>>& testPairs) {
    std::ifstream infile(testfile);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::string methodStr;
            int input;
            iss >> methodStr >> input;

            methodname method;
            if (methodStr == "add")
                method = methodname::add;
            else if (methodStr == "rmv")
                method = methodname::rmv;
            else
                method = methodname::ctn;
            // std::cout << methodStr <<", " << input << std::endl;
            testPairs.push_back({method, input});
        }
        infile.close();
    }
    std::cout << "load" << testPairs.size() << " test Pairs." << std::endl;
}

void loadOperationsFromFile(std::string testfile, std::vector<operation>& ops) {
    std::ifstream infile(testfile);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::string methodStr;
            int input;
            std::string outputStr;
            iss >> methodStr >> input >> outputStr;

            methodname method;
            if (methodStr == "add")
                method = methodname::add;
            else if (methodStr == "rmv")
                method = methodname::rmv;
            else
                method = methodname::ctn;

            bool output;
            output = outputStr == "true" ? true : false;
            // std::cout << methodStr <<", " << input << ", " << output <<
            // std::endl;
            ops.push_back(operation{method, input, output});
        }
        infile.close();
    }
}

void testOperations(std::vector<operation>& ops) {
    SetLib sl;
    std::vector<std::pair<int, operation>> errorOps;
    for(int i = 0; i < ops.size(); i++) {
        auto op = ops[i];
        bool ret;
        switch (op.method) {
            case add:
                printf("[OPERATION%3d] add(%d, %s)\n", i + 1, op.input,
                       op.output ? "true" : "false");
                ret = sl.add(op.input, op.output);
                break;
            case rmv:
                printf("[OPERATION%3d] rmv(%d, %s)\n", i + 1, op.input,
                       op.output ? "true" : "false");
                ret = sl.rmv(op.input, op.output);
                break;
            case ctn:
                printf("[OPERATION%3d] ctn(%d, %s)\n", i + 1, op.input,
                       op.output ? "true" : "false");
                ret = sl.ctn(op.input, op.output);
                break;
        }
        if (!ret) {
            errorOps.push_back({i + 1, op});
            std::cout << "!!ERROR OPERATION" << std::endl;
        }

        std::cout << "CURRENT SET: " << std::endl;
        sl.printSet();
        std::cout << std::endl;
    }

    // print error ops
    std::cout << "ERROR OPERATIONS" << std::endl;
    if (errorOps.size()) {
        std::for_each(errorOps.begin(), errorOps.end(), [](auto p) {
            switch (p.second.method) {
                case add:
                    printf("[OPERATION%3d] add(%d, %s)\n", p.first,
                           p.second.input, p.second.output ? "true" : "false");
                    break;
                case rmv:
                    printf("[OPERATION%3d] rmv(%d, %s)\n", p.first,
                           p.second.input, p.second.output ? "true" : "false");
                    break;
                case ctn:
                    printf("[OPERATION%3d] ctn(%d, %s)\n", p.first,
                           p.second.input, p.second.output ? "true" : "false");
                    break;
            }
        });
    } else
        std::cout << "\tNo Error Operation!" << std::endl;
}