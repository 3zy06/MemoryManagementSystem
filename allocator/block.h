#include <iostream>


struct block{
    int startAddress;
    int size;
    block* nextBlock;
    block* prevBlock;
};

void print()
{
    std::cout << "Hello WOrld" << std::endl;
}