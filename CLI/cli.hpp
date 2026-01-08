#include <iostream>
#include <vector>
#include <string>
#include "../Cache/cache.hpp"

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
        CacheLevel* level1 = NULL;
        CacheLevel* level2 = NULL;

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

                    if(level1 != NULL) level1->printStats(1);
                    if(level2 != NULL) level2->printStats(2);
                }
                if(SplitCommand[0] == "init" && SplitCommand[1] == "cache")
                {
                    std::string buffer; 

                    if(SplitCommand[2] == "1")
                    {
                        int size;
                        int blocksize;
                        int associativity;

                        std::cout << "Cache Size?" << std::endl;
                        std::getline(std::cin, buffer);
                        size = std::stoi(buffer);

                        std::cout << "Block Size?" << std::endl;
                        std::getline(std::cin, buffer);
                        blocksize = std::stoi(buffer);

                        std::cout << "Associativity?" << std::endl;
                        std::getline(std::cin, buffer);
                        associativity = std::stoi(buffer); 

                        level1 = new CacheLevel(size, blocksize, associativity, memory);
                    
                    }
                    if(SplitCommand[2] == "2")
                    {
                        int size;
                        int blocksize;
                        int associativity;

                        std::cout << "Cache Size?" << std::endl;
                        std::getline(std::cin, buffer);
                        size = std::stoi(buffer);

                        std::cout << "Block Size?" << std::endl;
                        std::getline(std::cin, buffer);
                        blocksize = std::stoi(buffer);

                        std::cout << "Associativity?" << std::endl;
                        std::getline(std::cin, buffer);
                        associativity = std::stoi(buffer); 

                        level2 = new CacheLevel(size, blocksize, associativity, memory);
                    }
                }
                if(SplitCommand[0] == "read")
                {
                    int addr = stoi(SplitCommand[1]);

                    if(level1 != NULL) 
                    {
                        if(level1->read(addr)) 
                        {
                            std::cout << "Found in level 1 cache" << std::endl;
                        }
                        else
                        {
                            if(level2 != NULL)
                            {
                                if(level2->read(addr))
                                {
                                    std::cout << "Found in level 2 cache" << std::endl;
                                    level1->insert(addr);
                                }
                                else
                                {
                                    std::cout << "Found in memory" << std::endl;
                                    
                                    level2->insert(addr);
                                    level1->insert(addr); 
                                }
                            }
                            else
                            {
                                std::cout << "Found in memory" << std::endl;
                                level1->insert(addr);
                            }
                        } 
                    }
                }
            }
            std::cout << "> ";
        }
    }
};