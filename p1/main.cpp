#include <iostream>

#include "cpu.h"

// enum to allow switch case using input strings
enum command { eOn, eSpawn, eRun, eSleep, eShutdown, eSize, eCapacity, eExit };
// converts input command strings to command type
command hashit(std::string c) {
    if (c == "ON") return eOn;
    if (c == "SPAWN") return eSpawn;
    if (c == "RUN") return eRun;
    if (c == "SLEEP") return eSleep;
    if (c == "SHUTDOWN") return eShutdown;
    if (c == "SIZE") return eSize;
    if (c == "CAPACITY") return eCapacity;
    return eExit;
}

int main() {
    // string to store commands
    std::string command;
    std::cin >> command;

    // instantiate PotentialField object
    CPU cpu;

    // keep program running until EXIT is reached
    while (hashit(command) != eExit) {
        switch (hashit(command)) {
            case eOn: {
                int n;
                std::cin >> n;
                std::cout << cpu.on(n) << std::endl;
                break;
            }
            case eSpawn: {
                int taskId;
                std::cin >> taskId;
                std::cout << cpu.spawn(taskId) << std::endl;
                break;
            }
            case eRun: {
                int coreId;
                std::cin >> coreId;
                std::cout << cpu.run(coreId) << std::endl;
                break;
            }
            case eSleep: {
                int coreId;
                std::cin >> coreId;
                std::cout << cpu.sleep(coreId) << std::endl;
                break;
            }
            case eShutdown: {
                std::cout << cpu.shutdown() << std::endl;
                break;
            }
            case eSize: {
                int coreId;
                std::cin >> coreId;
                std::cout << cpu.size(coreId) << std::endl;
                break;
            }
            case eCapacity: {
                int coreId;
                std::cin >> coreId;
                std::cout << cpu.capacity(coreId) << std::endl;
                break;
            }
        }

        // get next command
        std::cin >> command;
    }

    return 0;
}