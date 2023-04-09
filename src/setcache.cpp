#include "../include/setcache.h"

SetCache::SetCache(int set, int line) : 
    cache(vector<vector<CacheBlock>>(set, vector<CacheBlock>(line))), numSets(set), 
    linePerSet(line), lastCalled(NULL) {}

bool SetCache::read(unsigned short address, const vector<int> memory) {
    for (int i = 0; i < cache.size(); i++) {
        for (int j = 0; j < cache.at(i).size(); j++) {
            if (cache.at(i).at(j).tag == address && cache.at(i).at(j).valid) {
                lastCalled = &cache.at(i).at(j);
                return true;
            }
        }
    }

    unsigned short index = address % 4;
    unsigned short slot = (cache.at(index).at(0).age >= cache.at(index).at(1).age) ? 0 : 1;

    lastCalled = &cache.at(index).at(slot);

    lastCalled->tag = address;
    lastCalled->data = memory.at(address);
    lastCalled->valid = true;
    lastCalled->age = 0;
    cache.at(index).at((slot == 0) ? 1 : 0).age++;

    return false;
}

void SetCache::print() {
    cout << "Project 3 - Cache Simulator" << endl;
    cout << "+-----+";
    for (int i = 0; i < linePerSet; i++) { cout << "--------+--------+"; }
    cout << "\n| Set |";
    for (int i = 0; i < linePerSet; i++) { cout << "  Tag   |  Data  |"; }
    cout << "\n+-----+";
    for (int i = 0; i < linePerSet; i++) { cout << "--------+--------+"; }
    for (int i = 0; i < numSets; i++) {
        cout << "\n|  " << i << "  |";

        for (int j = 0; j < linePerSet; j++) {
            if (cache.at(i).at(j).valid) {
                bitset<4> binTag(cache.at(i).at(j).tag / 4);
                cout << "  " << binTag << "  |   " << hex << setw(2) << 
                        setfill('0') << uppercase << cache.at(i).at(j).data << "   |";
            }
            else {
                cout << "        |        |";
            }
        }

        cout << "\n+-----+";
        for (int i = 0; i < linePerSet; i++) { cout << "--------+--------+"; }
    }
    cout << "\n";
}

void SetCache::reset() {
    cache = vector<vector<CacheBlock>>(numSets, vector<CacheBlock>(linePerSet));
    lastCalled = NULL;
}