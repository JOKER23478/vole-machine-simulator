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
#include "Memory.h"
class Machine : public ALU, public Memory, public Register {
private:
    Register reg;
    Memory memory;
public:
    int Program_counter = 0;
    string Instruction_Register;

    void Display_menu() {
        cout << "1 - Input your file name (there is a problem in it can you implement it manually)\n2 - Input the instructions without filename\n3 - Exit the program\nEnter your choice:\n";
    }

    void Input_File_Name() {
        string filename;
        cout << "Enter your filename:\n";
        // cin >> filename;
        cout << "Attempting to open file: " << filename << endl; // Debugging output
        ifstream file(filename);
        if (!file) {
            cout << "Invalid filename. Please try again.\n";
            return;
        }
        string instruction;
        vector<string> instructions;
        while (file >> instruction) {
            instructions.push_back(instruction);
        }
        file.close();
        Load_Program(instructions);
    }


    void Load_Program(const vector<string>& instructions) {
        for (size_t addr = 0; addr < instructions.size() && addr < 256; ++addr) {
            memory.SetCell(addr, instructions[addr]);
        }
    }

    void Input_Instructions() {
        cout << "Enter your instructions (type 'end' to finish):\n";
        string instruction;
        int addr = 0;
        while (true) {
            cin >> instruction;
            if (instruction == "end") {
                break;
            }
            if (instruction.size() == 4 && is_valid(instruction)) {
                string part1 = instruction.substr(0, 2);
                string part2 = instruction.substr(2, 2);
                if (addr < 256) {
                    memory.SetCell(addr++, part1);
                    Program_counter = addr - 1;
                    Instruction_Register = part1 + part2;
                    Execute();
                }
                if (addr < 256) {
                    memory.SetCell(addr++, part2);
                    Program_counter = addr - 1;
                    Execute();
                }
            }
            else {
                cout << "Invalid instruction: " << instruction << ". Each instruction must be 4 valid hex characters.\n";
            }
        }
    }

    bool is_valid(const string& code) {
        for (char c : code) {
            if (!isxdigit(c)) return false;
        }
        return true;
    }

    void Execute() {
        if (Instruction_Register.empty()) return;

        int opcode = stoi(Instruction_Register.substr(0, 1), nullptr, 16);
        int reg1 = stoi(Instruction_Register.substr(1, 1), nullptr, 16);
        int reg2_mem = ALU::hextodec(Instruction_Register.substr(2, 2));
        switch (opcode) {
        case 1:
            load(reg1, reg2_mem);
            break;
        case 2:
            reg.Set_cell(reg1, reg2_mem);
            break;
        case 3:
            store(reg1, reg2_mem);
            break;
        case 4:
            move(reg1, reg2_mem);
            break;
        case 5:
            addTwoComplement(reg1, reg2_mem);
            break;
        case 7:
            bitwiseOR(reg1, reg2_mem, reg2_mem);
            break;
        case 8:
            bitwiseAND(reg1, reg2_mem, reg2_mem);
            break;
        case 9:
            bitwiseXOR(reg1, reg2_mem, reg2_mem);
            break;
        case 10:
            rotateRight(reg1, reg2_mem);
            break;
        case 11:
            jump(reg1, reg2_mem);
            return;
        case 12:
            halt();
            return;
        default:
            break;
        }
        Program_counter++;
    }

    void bitwiseOR(int regR, int regS, int regT) {
        if (regR < 0 || regR >= 16 || regS < 0 || regS >= 16 || regT < 0 || regT >= 16) {
            cout << "Error! Register index out of bounds" << std::endl;
            return;
        }
        int regValueS = reg.Get_cell(regS - 1);
        int regValueT = reg.Get_cell(regT);
        int result = regValueS | regValueT;
        reg.Set_cell(regR, result);
    }
    void bitwiseAND(int regR, int regS, int regT) {
        if (regR < 0 || regR >= 16 || regS < 0 || regS >= 16 || regT < 0 || regT >= 16) {
            cout << "Error! Register index out of bounds" << std::endl;
            return;
        }
        int regValueS = reg.Get_cell(regS - 1);
        int regValueT = reg.Get_cell(regT);
        int result = regValueS & regValueT;
        reg.Set_cell(regR, result);
    }


    void bitwiseXOR(int regR, int regS, int regT) {
        if (regR < 0 || regR >= 16 || regS < 0 || regS >= 16 || regT < 0 || regT >= 16) {
            cout << "Error! Register index out of bounds" << std::endl;
            return;
        }
        int regValueS = reg.Get_cell(regS - 1);
        int regValueT = reg.Get_cell(regT);
        int result = regValueS ^ regValueT;
        reg.Set_cell(regR, result);
    }
    void rotateRight(int regR, int steps) {
        if (regR < 0 || regR >= 16) {
            cout << "Error! Register index out of bounds" << std::endl;
            return;
        }
        int regValue = reg.Get_cell(regR);
        steps = steps % 8;
        int firstResult;
        if (steps % 2 == 0) {
            steps /= 2;
            firstResult = ((regValue >> steps) | (regValue << (8 - steps))) & 0xFF;
        }
        else {
            //there is a problem here  
            firstResult = ((regValue >> steps) | (regValue << (8 - steps))) & 0xFF;

        }
    }



    void load(int regIndex, int memAddress) {
        if (memAddress < 0 || memAddress >= 256) {
            cout << "Error! Address is out of bounds\n";
            return;
        }
        int value = ALU::hextodec(memory.GetCell(memAddress));
        reg.Set_cell(regIndex, value);
    }

    void store(int regIndex, int memAddress) {
        if (regIndex < 0 || regIndex >= 16 || memAddress < 0 || memAddress >= 256) {
            cout << "Error! Index out of bounds\n";
            return;
        }
        int regValue = reg.Get_cell(regIndex);
        memory.SetCell(memAddress, ALU::dectohexa(regValue));
    }
    void move(int srcReg, int destReg) {
        if (srcReg < 0 || srcReg >= 16 || destReg < 0 || destReg >= 16) {
            cout << "Error! Register index out of bounds\n";
            return;
        }
        int value = reg.Get_cell(srcReg);
        reg.Set_cell(destReg, value);
    }

    void addTwoComplement(int reg1, int reg2) {
        if (reg1 != reg2) {
            int regValue1 = reg.Get_cell(reg1);
            int regValue2 = reg.Get_cell(reg2);
            int result = regValue1 + regValue2;
            result = (result + 256) % 256;
            reg.Set_cell(reg1, result);
        }
        else {
            int regValue = reg.Get_cell(reg2 - 16);
            int res = (regValue * 2) % 256;
            reg.Set_cell(reg1, res);
        }
    }

    void jump(int address, int offset) {//there is a problem in the jump
        Program_counter = address + offset;
        cout << "Jumping to address " << Program_counter << endl;
    }

    void halt() {
        cout << "Program Halted\n";
    }

    void DisplayModifications() {
        cout << "\nModified Registers:\n";
        reg.Display();
        cout << "\nModified Memory:\n";
        memory.DisplayMemory();
    }

    void Run() {
        while (Program_counter < 256) {
            Instruction_Register = memory.GetCell(Program_counter);
            Execute();
        }
    }
};
