/**** This is a helper/skeleton code for the assignment     ****/
/**** Author: Sarbojit Das                                  ****/
/**** Compile using command g++ helper_code.cpp -lpthread ****/

#include<iostream>
#include<thread>
#include"SetLib.cpp"
#include<vector>
#include"LinearizedSeq.cpp"

using namespace std;

template <class T> 
void worker_func(int thread_id, T *set, vector<operation> test_case){
  for (auto it = test_case.begin(); it != test_case.end(); ++it) {
//Do the operation from the test case
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

  std::cout << "Worker "<<thread_id<<" completed" << endl;
}

void monitor_func(int N_Threads){
  //Pick the first operation from the sequence.
  // Check the element that you picked
  cout << "Monitor completed" << endl;
}

void task1(){
}

void task2(){
}

void task3(){
  int N_Threads = 3;
  thread *worker= new thread[N_Threads];
  //SetList *set = new SetList();
//Run workers------------------
  for (int i=0; i<N_Threads; i++){
    vector<operation> test_case;
    //fill test_case with your sequence of operations
    //worker[i]=thread(worker_func<SetList>, i, ref(set), test_case);		
  }

  for (int i=0; i<N_Threads; i++){
    //worker[i].join();	
  }
//------------------------------
//Run monitor-------------------
  thread monitor = thread(monitor_func, N_Threads);
  monitor.join();
//------------------------------
  //delete set;
}

void task4(){
}

int main(){
  task1();
  task2();
  task3();
  task4();
  return 0;
}
