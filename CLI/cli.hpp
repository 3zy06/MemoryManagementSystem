#include <iostream>
#include <vector>
#include "../allocator/allocator.hpp"
struct CLI{
    bool running;

    std::vector<std::string> split(std::string s)
    {
        std::vector <std::string> SplitCommand;
        std::string temp;
        for(auto c: s)
        {
            if(c == ' ') 
            {
                if(temp.size())SplitCommand.push_back(temp);
                temp = "";
            }
            else temp.push_back(c);
        }
        if(temp.size()) SplitCommand.push_back(temp);

        return SplitCommand;
    }

    void run()
    {
        std::string command;
        Memory* memory = NULL;

        std::cout << "> ";
        int Allocator = 1;
        while (std::getline(std::cin, command)) 
        {
            if (command == "exit") 
            {
                std::cout << "Exiting...\n";
                break;
            }
            else
            {
                std::vector<std::string> SplitCommand = split(command);
            
                
                if(SplitCommand[0] == "init" && SplitCommand[1] == "memory")
                {
                    memory = new Memory(stoi(SplitCommand[2]));
                }
                if(SplitCommand[0] == "malloc")
                {
                    if(Allocator == 1) memory->FirstFit(stoi(SplitCommand[1]));
                    if(Allocator == 2) memory->BestFit(stoi(SplitCommand[1]));
                    if(Allocator == 3) memory->WorstFit(stoi(SplitCommand[1]));
                }
                if(SplitCommand[0] == "free")
                {
                    memory->Free(stoi(SplitCommand[1]));
                }
                if(SplitCommand[0] == "dump" && SplitCommand[1] == "memory")
                {
                    memory->printMemory();
                }
                if(SplitCommand[0] == "set" && SplitCommand[1] == "allocator")
                {
                    if(SplitCommand[2] == "first_fit") Allocator = 1;
                    if(SplitCommand[2] == "best_fit") Allocator = 2;
                    if(SplitCommand[2] == "worst_fit") Allocator = 3;
                }
                if(SplitCommand[0] == "stats")
                {
                    memory->Stats();
                }
            
            }
            std::cout << "> ";
            
        }
    }
};