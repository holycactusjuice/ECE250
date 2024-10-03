#include "cpu.h"

#include <climits>
#include <iostream>
#include <string>

#include "deque.h"

// trivial constructor
CPU::CPU() : coreCount(0), cores(nullptr) {}

CPU::~CPU() {
    for (int i = 0; i < coreCount; i++) {
        cores[i].~Deque();
    }
    delete[] cores;
    cores = nullptr;
}

int CPU::getCoreWithLeastTasks(int exception) {
    // find the core with the least tasks
    // only update if striclty smaller
    // as per requirement that if two cores have the same size
    // we choose the one with the smaller index
    int minSize = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < coreCount; i++) {
        if (i == exception) {
            continue;
        }
        if (cores[i].getSize() < minSize) {
            minSize = cores[i].getSize();
            minIndex = i;
        }
    }
    return minIndex;
}

int CPU::getCoreWithMostTasks(int exception) {
    // find the core with the most tasks
    // only update if striclty larger
    // as per requirement that if two cores have the same size
    // we choose the one with the smaller index
    int maxSize = INT_MIN;
    int maxIndex = -1;
    for (int i = 0; i < coreCount; i++) {
        if (i == exception) {
            continue;
        }
        if (cores[i].getSize() > maxSize) {
            maxSize = cores[i].getSize();
            maxIndex = i;
        }
    }
    return maxIndex;
}

std::string CPU::on(int n) {
    // check if core exists
    if (cores != nullptr) {
        return "failure";
    }
    coreCount = n;
    // create new core
    // this already allocates memory for Deque objects
    // so we don't need to do anything else
    cores = new Deque[coreCount];
    return "success";
}

std::string CPU::spawn(int taskId) {
    // check if task id is nonpositive
    if (taskId < 1) {
        return "failure";
    }
    // find the core with the smallest size
    int minIndex = getCoreWithLeastTasks(-1);
    // push the task to the core
    cores[minIndex].pushBack(taskId);
    return "core " + std::to_string(minIndex) + " assigned task " +
           std::to_string(taskId);
}

std::string CPU::run(int coreId) {
    // check if core id is within bounds
    if (coreId < 0 || coreId >= coreCount) {
        return "failure";
    }
    // check if core has tasks to begin with
    // need this bool to return the correct message
    bool hadTasks = (cores[coreId].getSize() > 0);
    int taskId = hadTasks ? cores[coreId].popFront() : -1;
    // if core is now empty, assign a task from the core with the most tasks
    if (cores[coreId].getSize() == 0) {
        int maxIndex = getCoreWithMostTasks(coreId);
        // make sure that the core with the most tasks has at least 1 task
        if (cores[maxIndex].getSize() > 0) {
            int taskId = cores[maxIndex].popBack();
            cores[coreId].pushBack(taskId);
        }
    }
    return hadTasks ? "core " + std::to_string(coreId) + " is running task " +
                          std::to_string(taskId)
                    : "core " + std::to_string(coreId) + " has no tasks to run";
}

std::string CPU::sleep(int coreId) {
    // check if core id is within bounds
    if (coreId < 0 || coreId >= coreCount) {
        return "failure";
    }
    // check if core's queue is empty
    if (cores[coreId].getSize() == 0) {
        return "core " + std::to_string(coreId) + " has no tasks to assign";
    }
    std::string result = "";
    // pop tasks until empty
    while (cores[coreId].getSize() > 0) {
        int taskId = cores[coreId].popBack();
        int coreWithLeastTasks = getCoreWithLeastTasks(coreId);
        cores[coreWithLeastTasks].pushBack(taskId);
        result += "task " + std::to_string(taskId) + " assigned to core " +
                  std::to_string(coreWithLeastTasks) + " ";
    }
    return result;
}

std::string CPU::shutdown() {
    // check if there are tasks left in any core
    bool hasTasks = false;
    std::string result = "";
    for (int i = 0; i < coreCount; i++) {
        if (cores[i].getSize() > 0) {
            hasTasks = true;
            while (cores[i].getSize() > 0) {
                result += "deleting task " +
                          std::to_string(cores[i].popFront()) + " from core " +
                          std::to_string(i) + " ";
            }
        }
    }
    if (!hasTasks) {
        return "no tasks to remove";
    }
    return result;
}

std::string CPU::size(int coreId) {
    // check if core id is within bounds
    if (coreId < 0 || coreId >= coreCount) {
        return "failure";
    }
    // get the size of the core's queue
    return std::to_string(cores[coreId].getSize());
}

std::string CPU::capacity(int coreId) {
    // check if core id is within bounds
    if (coreId < 0 || coreId >= coreCount) {
        return "failure";
    }
    // get the capacity of the core's queue
    return std::to_string(cores[coreId].getCapacity());
}