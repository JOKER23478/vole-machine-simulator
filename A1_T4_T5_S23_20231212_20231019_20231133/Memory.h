#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <sstream>
#include <bitset>
#include "ALU.h"
#include "Register.h"
class Memory {
private:
    string memory[256];  // 256-byte memory

public:
    Memory() {
        // Initialize memory to 00
        for (int i = 0; i < 256; i++) {
            memory[i] = "00";
        }
    }

    // Set memory value at a specific address
    void SetCell(int address, string value) {
        if (address >= 0 && address < 256) {
            memory[address] = value;
        }
        else {
            cout << "Error! Memory address out of bounds\n";
        }
    }

    // Get memory value at a specific address
    string GetCell(int address) {
        if (address >= 0 && address < 256) {
            return memory[address];
        }
        else {
            cout << "Error! Memory address out of bounds\n";
            return "00";  // Return a default value if out of bounds
        }
    }

    // Display memory state (debugging purposes)
    void DisplayMemory() {
        cout << "Memory State:\n";
        for (int i = 0; i < 256; i++) {
            cout << memory[i] << " ";
            if ((i + 1) % 16 == 0) {
                cout << endl;
            }
        }
    }
};
