#include <queue>
#include <mutex>

enum methodname {add, rmv, ctn};
typedef struct _operation{
  //blah blah blah
  methodname method;
  int input;
  bool output;
} operation;

std::queue<operation> Linearized_seq;
