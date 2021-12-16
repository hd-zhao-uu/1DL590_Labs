#ifndef STACKPAIR_H  // include guard
#define STACKPAIR_H
#include <string>

namespace StackPair{
    enum methodname {push, pop, size};

    typedef struct _StackPair{
    methodname method;
    std::string input;
    } StackPair;
}


#endif