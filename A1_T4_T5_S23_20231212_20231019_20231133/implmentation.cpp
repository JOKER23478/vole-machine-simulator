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
#include "Machine.h"
using namespace std;
int main() {
    Machine machine;
    char choice;
    while (true) {
        machine.Display_menu();
        cin >> choice;
        switch (choice) {
        case '1'://it isn t working 
            machine.Input_File_Name();
            machine.Run();
            machine.DisplayModifications();
            break;
        case '2':
            machine.Input_Instructions();
            machine.Run();
            machine.DisplayModifications();
            break;
        case '3':
            return 0;
        default:
            cout << "Invalid choice! Try again.\n";
            break;
        }
    }
}
