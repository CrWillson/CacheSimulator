#include "../include/setcache.h"
#include <string>

using namespace std;

void clear() {
    for (int i = 0; i < 10; i++) { cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; }
}

bool is_integer(const std::string& str)
{
    try {
        stoi(str);
        return true;
    }
    catch (...) {
        return false;
    }
}

int main(int argc, char** argv) {
    SetCache cache(4, 2);
    float numHits = 0.0f;
    float numMiss = 0.0f;

    vector<int> mainMemory = {
        0x92, 0x70, 0x8C, 0xFD, 0x89, 0xE2, 0x40, 0xC2, 
        0x0D, 0x9A, 0xD1, 0xF8, 0x43, 0x7E, 0xB7, 0x75, 
        0xFB, 0x44, 0xDD, 0xF6, 0xA6, 0x43, 0x11, 0x17,
        0x98, 0x88, 0x08, 0x6A, 0x6D, 0xB8, 0xBC, 0x12,
        0x0A, 0xF1, 0x4C, 0x45, 0x63, 0x2C, 0x40, 0x98,
        0x91, 0x65, 0x0E, 0x76, 0xEE, 0x5D, 0x18, 0x29,
        0x85, 0x13, 0x60, 0xC5, 0x56, 0xF2, 0x89, 0x9E,
        0x06, 0xE2, 0x0B, 0xA2, 0xB2, 0x41, 0xB1, 0x7B
    }; 

    string input = "";
    short address = 0;
    bool wasHit = false;
    float hitRatio = 0.0f;

    clear();
    cache.print();
    cout << "\n ----  |  Hit Ratio: 0.0%" << endl;
    cout << "   Last address: n/a" << endl;
    cout << "   Tag: ----   |   Data: --" << endl;

    cout << "\nEnter an address 00 - 63 ('r' to reset, 'q' to quit): ";
    cin >> input;
    while (input != "q") {
        if (is_integer(input)) {
            address = stoi(input);

            if (address < 0 || address > mainMemory.size() - 1) {
                clear();
                cache.print();
                cout << "\n   Invalid address entered." << endl;
                cout << dec << "   Last address: " << address << endl;
                cout << "   Tag: ----   |   Data: --" << endl;
            }
            else {
                wasHit = cache.read(address, mainMemory);

                clear();
                cache.print();

                if (wasHit) {
                    numHits++;
                    cout << "\n   HIT  ";
                }
                else {
                    numMiss++;
                    cout << "\n   MISS ";
                }

                hitRatio = (numHits / (numHits + numMiss)) * 100;
                cout << " |  Hit Ratio: " << fixed << setprecision(1) << hitRatio << "%" << endl;
                cout << dec << "   Last address: " << address << endl;
                
                CacheBlock* lastCall = cache.getLastCalled();
                bitset<4> binTag(lastCall->tag / 4);
                cout << "   Tag: " << binTag << "   |   Data: ";
                cout << hex << setw(2) << setfill('0') << uppercase << lastCall->data << endl;

            }

            
        }
        else if (input == "r") {
            numHits = 0;
            numMiss = 0;
            cache.reset();
            clear();
            cache.print();
            cout << "\n ----  |  Hit Ratio: 0.0%" << endl;
            cout << "   Last address: n/a" << endl;
            cout << "   Tag: ----   |   Data: --" << endl;
        }
        else {
            clear();
            cache.print();
            cout << "\n   Invalid input entered." << endl;
            cout << dec << "   Last address: " << address << endl;
            cout << "   Tag: ----   |   Data: --" << endl;
        }

        cout << "\nEnter an address 00 - 63 ('r' to reset, 'q' to quit): ";
        cin >> input;
    }

    return 0;
}