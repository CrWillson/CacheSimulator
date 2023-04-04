#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <bitset>
#include "../include/InvalidAddressException.h"

using namespace std;

struct CacheBlock {
    bool valid;
    unsigned short tag;
    unsigned short data;
    int age;

    CacheBlock() : valid(false), tag(0), data(0x0), age(0) {};
};

class SetCache {
    public:
        SetCache(int line, int set);
        bool read(unsigned short address, const vector<int> memory);
        void print();
        
    private:
        //map<int, int> cache;
        vector<vector<CacheBlock>> cache;
        int numSets;
        int linePerSet;

};