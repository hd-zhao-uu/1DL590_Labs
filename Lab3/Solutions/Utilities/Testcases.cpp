#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include "../Datastructures/Pair.h"
#include "../Datastructures/StackPair.h"


void createTestCases(int randStart,
                     int randEnd,
                     int size,
                     std::vector<Pair>& testPairs) {
    /*
        Create testcases randomly with no extra requirements.
    */

    testPairs.clear();
    // initialize random seed: */
    std::srand(std::time(NULL));
    methodname methods[3] = {add, rmv, ctn};
    methodname method;
    int value;

    for (int i = 0; i < size; i++) {
        method = methods[rand() % 3];
        value = rand() % (randEnd - randStart + 1) +
                randStart;  // [randStart, randEnd]
        testPairs.push_back({method, value});
    }

    printf("[DEBUG] Load %ld test Pairs.\n", testPairs.size() );
}

void createTestCases(int randStart,
                     int randEnd,
                     int size,
                     int i,
                     std::vector<Pair>& testPairs) {
    /*
        Create testcases randomly.

        `i` % of the operations are cnt()
        From the remaining set, 90% should be add, and 10% should rmv().

    */

    testPairs.clear();
    // initialize random seed: */
    std::srand(std::time(NULL));
    int addSize, rmvSize, ctnSize;
    ctnSize = size * ((double)i/100);
    addSize = (size - ctnSize) * 0.9, rmvSize = (size-ctnSize) * 0.1;

    int value;

    for (int i = 0; i < addSize; i++) {
        value = rand() % (randEnd - randStart + 1) +
                randStart;  // [randStart, randEnd]
        testPairs.push_back({add, value});
    }

    for (int i = 0; i < rmvSize; i++) {
        value = rand() % (randEnd - randStart + 1) +
                randStart;  // [randStart, randEnd]
        testPairs.push_back({rmv, value});
    }

    for (int i = 0; i < ctnSize; i++) {
        value = rand() % (randEnd - randStart + 1) +
                randStart;  // [randStart, randEnd]
        testPairs.push_back({ctn, value});
    }

    printf("[DEBUG] Load %ld test Pairs(ctn: %d, add: %d, rmv: %d). \n", testPairs.size(), ctnSize, addSize, rmvSize);
}


void createTestCases(int randStart,
                     int randEnd,
                     int size,
                     std::vector<StackPair::StackPair>& testPairs) {
    /*
        Create testcases randomly with no extra requirements.
    */

    testPairs.clear();
    // initialize random seed: */
    std::srand(std::time(NULL));
    StackPair::methodname methods[3] = {StackPair::push, StackPair::pop, StackPair::size};
    StackPair::methodname method;
    int value;

    for (int i = 0; i < size; i++) {
        method = methods[rand() % 3];
        if(method == StackPair::push) {
            value = rand() % (randEnd - randStart + 1) +
                randStart;  // [randStart, randEnd]
                testPairs.push_back({method, std::to_string(value)});
        }
        else {
            testPairs.push_back({method, ""});
        }
    }

    printf("[DEBUG] Load %ld test Stack Pairs.\n", testPairs.size() );
}
