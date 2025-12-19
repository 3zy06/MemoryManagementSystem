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

    void invalidCommand()
    {

    }

    void run()
    {
        std::string command;
        Memory* memory = NULL;

        std::cout << "> ";
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
                // std::cout << "> ";
                if(!SplitCommand.size()) invalidCommand();
                else
                {
                    if(SplitCommand[0] == "init" && SplitCommand[1] == "memory")
                    {
                        try
                        {
                            if(memory != NULL) throw 505;
                            memory = new Memory(stoi(SplitCommand[2])); 
                        }
                        catch(const std::exception& e)
                        {
                            invalidCommand();
                            std::cerr << e.what() << '\n';
                        }
                    }
                    if(SplitCommand[0] == "malloc")
                    {
                        try
                        {
                            memory->FirstFit(stoi(SplitCommand[1]));
                        }
                        catch(const std::exception& e)
                        {
                            invalidCommand();
                            std::cerr << e.what() << '\n';
                        }
                        // allocate
                    }
                    if(SplitCommand[0] == "dump" && SplitCommand[1] == "memory")
                    {
                        // print memory
                        try
                        {
                            memory->printMemory();
                        }
                        catch(const std::exception& e)
                        {
                            invalidCommand();
                            std::cerr << e.what() << '\n';
                        }
                    }
                }
            }
            std::cout << "> ";
            
        }
    }
};