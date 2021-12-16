#ifndef STACKOPERATION_H  // include guard
#define STACKOPERATION_H

#include <string>
#include "StackPair.h"

typedef struct _StackOperation{
  StackPair::methodname method;
  std::string input;
  std::string output; // if output is bool, then true = 1, false = 0

  _StackOperation() {}

  _StackOperation(StackPair::StackPair p) {
      method = p.method;
      input = p.input;
      output = "";
  }

  _StackOperation(StackPair::methodname method,  std::string input, std::string output): 
    method(method), input(input), output(output) {}

} StackOperation;

#endif