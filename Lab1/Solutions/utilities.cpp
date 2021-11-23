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
    std::cout << "load " << testPairs.size() << " test Pairs." << std::endl;
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

