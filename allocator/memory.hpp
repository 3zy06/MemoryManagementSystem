#include <iostream>


struct Block{
    int StartAddress;
    int Size;
    int Id;
    bool Hole;
    Block* NextBlock;
    Block* PrevBlock;

    Block(int startAddress, int size, int id, int hole, Block* nextBlock, Block* prevBlock)
    {
        StartAddress = startAddress;
        Size = size;
        Id = id;
        Hole = hole;
        NextBlock = nextBlock;
        PrevBlock = prevBlock; 
    }
};

struct Memory{
    Block* Head;
    int Id;

    Memory(int size)
    {
        Id = 0;
        Head = new Block(0, size, 1, 1, NULL, NULL);

        std::cout << "Created memory of Size " << size << std::endl;
    }

    void printMemory()
    {
        Block* node = Head;
        while(node != NULL)
        {
            if(node->Hole) std::cout << "free";
            else std::cout << "used, id = " << node->Id;
            std::cout << std::endl; 
        
            if(node->NextBlock != NULL) node = node->NextBlock;
            else node = NULL;
        }
    }

    void FirstFit(int size)
    {

        bool found = false;
        Block* node = Head;
        while(node != NULL && !found) 
        {
            if(node->Hole)
            {
                if(node->Size >= size)
                {
                    int extra = node->Size - size;
                    node->Size = size;
                    int endAddress = node->StartAddress + node->Size;
                    node->Hole = 0;
                    Block* After = node->NextBlock;
                    Block* Before = new Block(endAddress, extra, ++Id, 1, After, node);
                    node->NextBlock = Before; 
                    found = true;
                    std::cout << "Allocated block id = " << Id << " at address " << node->StartAddress << std::endl;
                }
            }
            if(node->NextBlock != NULL) node = node->NextBlock;
            else node = NULL;
        }
        if(!found) std::cout << "Not enough Memory" << std::endl;
    }
};

void print()
{
    std::cout << "Hello WOrld" << std::endl;
}