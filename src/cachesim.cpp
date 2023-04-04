#include "../include/setcache.h"

using namespace std;

void clear() {
    for (int i = 0; i < 30; i++) { cout << endl; }
}

int main(int argc, char** argv) {
    SetCache cache(4, 2);
    float numHits = 0.0f;
    float numMiss = 0.0f;

    vector<int> mainMemory = {
        0x92, 0x70, 0x8C, 0xFD, 0x89, 0xE2, 0x40, 0xC2, 
        0x0D, 0x9A, 0xD1, 0xF8, 0x43, 0x7E, 0xB7, 0x75, 
        0xFB
    }; 

    short address = true;
    bool wasHit = false;
    float hitRatio = 0.0f;

    clear();
    cache.print();
    cout << "\n       | Hit Ratio: 0.0%" << endl;
    cout << "\nEnter an address (00 - 63): ";
    cin >> address;
    while (address != -1) {
        if (address < 0 || address > mainMemory.size() - 1) {
            clear();
            cache.print();
            cout << "\n   Invalid address entered." << endl;
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
            cout << " | Hit Ratio: " << fixed << setprecision(1) << hitRatio << "%" << endl;
                
        }

        cout << "\nEnter an address (00 - 63): ";
        cin >> address;
    }

    return 0;
}