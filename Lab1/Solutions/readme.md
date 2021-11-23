# 1DL590 Lab 1


## Compile and Execute
- **Compile**: g++ Experiments.cpp -lpthread -o ex.o
- **Execute**: ./ex.o


## Structure
- Folder: `testcases`: Store the testcases used in `Experiment.cpp`. `create_testpairs.py` is a Python script to generate pairs for testing.
- `utilities.cpp`: Functions to help to finish tasks in `Experiment.cpp`.They load testcases from the folder: `testcases`.
- `Node.h`: header file of the Node used in `SetList.cpp` and `CoarseSet.cpp`.
- Others are the skeleton code and the files required in the tasks.