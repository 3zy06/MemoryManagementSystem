#include <iostream>
#include "allocator/allocator.hpp"
int main()
{
    print();
    Memory memory(1024);
    memory.FirstFit(100);
    memory.FirstFit(500);
    memory.FirstFit(400);
    memory.FirstFit(100);


    std::string command;

    std::cout << "> ";
    while (std::getline(std::cin, command)) {
        if (command == "exit") {
            std::cout << "Exiting...\n";
            break;
        }
        
        
    }



}