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
            if(node->Hole) std::cout << node->StartAddress << " - " << node->StartAddress+node->Size-1 << " free";
            else std::cout << node->StartAddress << " - " << node->StartAddress+node->Size-1 << " used, id = " << node->Id;
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
                    node->Id = ++Id;
                    found = true;
                    if(extra)
                    {
                        Block* After = node->NextBlock;
                        Block* Before = new Block(endAddress, extra, 0, 1, After, node);
                        node->NextBlock = Before; 
                        if(After != NULL) After->PrevBlock = Before;
                    }
                    std::cout << "Allocated block id = " << node->Id << " at address " << node->StartAddress << std::endl;
                }
            }
            if(node->NextBlock != NULL) node = node->NextBlock;
            else node = NULL;
        }
        if(!found) 
        {
            std::cout << "Not enough Memory" << std::endl;
            return;
        }

    }

    void BestFit(int size)
    {

        bool found = false;
        Block* node = Head;
        int best_size = 1e9;
        while(node != NULL) 
        {
            if(node->Hole)
            {
                if(node->Size >= size)
                {
                    found = true;
                    if(node->Size < best_size) best_size = node->Size;
                }
            }
            if(node->NextBlock != NULL) node = node->NextBlock;
            else node = NULL;
        }
        if(!found) 
        {
            std::cout << "Not enough Memory" << std::endl;
            return;
        }

        node = Head;
        found = false;
        while(node != NULL && !found) 
        {
            if(node->Hole)
            {
                if(node->Size == best_size && !found)
                {
                    int extra = node->Size - size;
                    node->Size = size;
                    int endAddress = node->StartAddress + node->Size;
                    node->Hole = 0;
                    node->Id = ++Id;
                    found = true;
                    if(extra)
                    {
                        Block* After = node->NextBlock;
                        Block* Before = new Block(endAddress, extra, 0, 1, After, node);
                        node->NextBlock = Before; 
                        if(After != NULL) After->PrevBlock = Before;
                    }
                    std::cout << "Allocated block id = " << node->Id << " at address " << node->StartAddress << std::endl;
                }
            }
            if(node->NextBlock != NULL) node = node->NextBlock;
            else node = NULL;
        }
    }

    void WorstFit(int size)
    {

        bool found = false;
        Block* node = Head;
        int best_size = 0;
        while(node != NULL) 
        {
            if(node->Hole)
            {
                if(node->Size >= size)
                {
                    found = true;
                    if(node->Size > best_size) best_size = node->Size;
                }
            }
            if(node->NextBlock != NULL) node = node->NextBlock;
            else node = NULL;
        }
        if(!found) 
        {
            std::cout << "Not enough Memory" << std::endl;
            return;
        }

        node = Head;
        found = false;
        while(node != NULL && !found) 
        {
            if(node->Hole)
            {
                if(node->Size == best_size && !found)
                {
                    int extra = node->Size - size;
                    node->Size = size;
                    int endAddress = node->StartAddress + node->Size;
                    node->Hole = 0;
                    node->Id = ++Id;
                    found = true;
                    if(extra)
                    {
                        Block* After = node->NextBlock;
                        Block* Before = new Block(endAddress, extra, 0, 1, After, node);
                        node->NextBlock = Before; 
                        if(After != NULL) After->PrevBlock = Before;
                    }
                    std::cout << "Allocated block id = " << node->Id << " at address " << node->StartAddress << std::endl;
                }
            }
            if(node->NextBlock != NULL) node = node->NextBlock;
            else node = NULL;
        }
    }

    void Free(int id)
    {
        bool found = false;
        Block* node = Head;
        while(node != NULL && !found) 
        {
            if(!node->Hole)
            {
                if(node->Id == id)
                {
                    
                    node->Id = 0;
                    node->Hole = true;
                    Block* After = node->NextBlock;
                    Block* Before = node->PrevBlock;
                    if(After != NULL && After->Hole)
                    {
                        node->Size += After->Size;
                        node->NextBlock = After->NextBlock;
                        if(After->NextBlock != NULL) After->NextBlock->PrevBlock = node;
                    }
                    if(Before != NULL && Before->Hole)
                    {
                        node->Size += Before->Size;
                        node->StartAddress = Before->StartAddress;
                        node->PrevBlock = Before->PrevBlock;
                        if(Before->PrevBlock != NULL) Before->PrevBlock->NextBlock = node;
                    }
                }
            }
            if(node->NextBlock != NULL) node = node->NextBlock;
            else node = NULL;
        }
    }

    void Stats()
    {
        int total_free = 0;
        int largest_free = 0;
        int total_memory = 0;
        Block* node = Head;
        while(node != NULL)
        {
            if(node->Hole) 
            {
                total_free += node->Size;
                if(node->Size > largest_free) largest_free = node->Size;
            }
            total_memory += node->Size;
            if(node->NextBlock != NULL) node = node->NextBlock;
            else node = NULL;
        }
        std::cout << "Total Memory " << total_memory << std::endl;
        std::cout << "Used Memory " << total_memory - total_free << std::endl;
        std::cout << "Free Memory " << total_free << std::endl;
        std::cout << "External Fragmentation " << (1 - (1.0*largest_free / total_free))*100.0 << std::endl;



    }
};

void print()
{
    std::cout << "Hello WOrld" << std::endl;
}