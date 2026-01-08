#include <iostream>
#include <vector>
#include <set>
#include "../Memory/memory.hpp"
#include <cmath>
#include <bitset>
#include <deque>


struct CacheLine{
    int Tag;
    int Data;

    CacheLine(int tag, int data)
    {
        Tag = tag;
        Data = data;
    }
};

struct CacheLevel{
    int Size;
    int BlockSize;
    int Associativity;
    Memory* memory;

    int offset_bits;
    int index_bits;
    int num_sets;

    int Hits;
    int Misses;

    std::vector <std::deque<CacheLine>> Cache;

    CacheLevel(int size, int blocksize, int associativity, Memory* mem)
    {
        Size = size;
        BlockSize = blocksize;
        Associativity = associativity;
        num_sets = Size / (Associativity * BlockSize);

        Cache.resize(num_sets);
        offset_bits = log2(BlockSize);
        index_bits  = log2(Cache.size());

        memory = mem;

        Hits = 0;
        Misses = 0;

    }

    void insert(int address)
    {
        
        int offset = address & ((1 << offset_bits) - 1);
        int index  = (address >> offset_bits) & ((1 << index_bits) - 1);
        int tag    = address >> (offset_bits + index_bits);

        for(auto cl: Cache[index])
        {
            if(cl.Tag == tag) return; 
        }

        if(Cache[index].size() == Associativity)
        {
            CacheLine evicted = Cache[index].back();
            Cache[index].pop_back();
        }


        CacheLine CL(tag, 0);
        Cache[index].push_front(CL);


    }

    

    bool read(int address)
    {
        int offset = address & ((1 << offset_bits) - 1);
        int index  = (address >> offset_bits) & ((1 << index_bits) - 1);
        int tag    = address >> (offset_bits + index_bits);

        for(auto cl: Cache[index])
        {
            if(cl.Tag == tag) 
            {
                Hits++;
                return true;
            }
        }

        Misses++;

        return false;

    }

    void printStats(int id)
    {
        int total_accesses = Hits + Misses;
        double hit_ratio = (total_accesses > 0) ? (double)Hits / total_accesses : 0.0;

        std::cout << "Level " << id << " Cache Stats" << std::endl;
        std::cout << "Hits: " << Hits << std::endl;
        std::cout << "Misses: " << Misses << std::endl;
        std::cout << "Hit Ratio: " << std::fixed << std::setprecision(2) << hit_ratio * 100.0 << "%" << std::endl;
    }



};