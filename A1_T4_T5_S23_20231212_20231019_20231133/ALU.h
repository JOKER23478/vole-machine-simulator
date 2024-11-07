#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <sstream>
#include <bitset>
using namespace std;
class ALU {
public:
    string dectohexa(int decimal) {
        stringstream ss;
        ss << hex << uppercase << setw(2) << setfill('0') << decimal;
        return ss.str();
    }

    // Convert hexadecimal string to decimal
    int hextodec(string hexVal) {
        int decimal;
        stringstream ss;
        ss << hex << hexVal;
        ss >> decimal;
        return decimal;
    }
    int binToDec(string bin) {
        int m = 0;
        for (int i = 0; i < bin.size(); i++) {
            int n = bin[i] - '0';
            m = m * 2 + n;
        }
        return m;
    }

    string decToBin(int dec) {
        string m = "";
        if (dec == 0) {
            m = '0';
        }
        while (dec > 0) {
            if (dec % 2 == 1) {
                m += '1';
            }
            else if ((dec % 2) == 0) {
                m += '0';
            }
            dec = dec / 2;
        }
        reverse(m.begin(), m.end());
        return m;
    }

    string decToBin8Bit(int dec) {
        string str = decToBin(dec);
        while (str.size() < 8) {
            str = '0' + str;
        }
        return str;
    }
};
