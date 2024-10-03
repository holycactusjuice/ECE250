#ifndef CPU_H
#define CPU_H

#include <string>

#include "deque.h"

class CPU {
   private:
    int coreCount;
    Deque *cores;

    int getCoreWithLeastTasks(int exception);
    int getCoreWithMostTasks(int exception);

   public:
    CPU();
    ~CPU();

    // all command functions will return true or false
    // true if success and false if failure
    // in some cases the result message may be different
    std::string on(int n);
    std::string spawn(int taskId);
    std::string run(int coreId);
    std::string sleep(int coreId);
    std::string shutdown();
    std::string size(int coreId);
    std::string capacity(int coreId);
};

#endif