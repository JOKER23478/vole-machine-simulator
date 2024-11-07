#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <sstream>
#include <bitset>
class Register :public ALU {
private:
    int reg[16];  // Registers array

public:
    Register() {
        // Initialize registers to 0
        for (int i = 0; i < 16; i++) {
            reg[i] = 0;
        }
    }

    // Set register value
    void Set_cell(int index, int value) {
        if (index >= 0 && index < 16) {
            reg[index] = value;
        }
        else {
            cout << "Error! Register index out of bounds\n";
        }
    }

    // Get register value
    int Get_cell(int index) {
        if (index >= 0 && index < 16) {
            return reg[index];
        }
        else {
            return -1;  // Return an error value
        }
    }

    // Display register state
    void Display() {
        cout << "Register State:\n";
        for (int i = 0; i < 16; ++i) {
            cout << "reg (" << dectohexa(i) << ") : " << dectohexa(reg[i]) << endl;
        }
    }
};
