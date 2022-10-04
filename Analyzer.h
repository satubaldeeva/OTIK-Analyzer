//
// Created by Grigory on 02/10/2022.
//

#ifndef OTIK_ANALYZER_ANALYZER_H
#define OTIK_ANALYZER_ANALYZER_H

#include <vector>
#include <Algorithm>
#include <iomanip>
#include <cmath>

#include "functions.h"

#define BUFF_SIZE 10

using namespace std;

class Analyzer {
private:
    vector<pair<wstring, int>> symbols;
    string file;
    Alphabet alphabet;
    string info_file;
    int file_size;

public:

    Analyzer(const string& file, Alphabet alphabet_type);
    void processFile();
    void analyzeByte(const char* currentByte);
    void analyzeUTF8(const wchar_t currentSymbol);
    void makeReportFile();

    //comparators to sort symbols array
    struct namesDescending
    {
        inline bool operator() (const pair<wstring, int>& a, const pair<wstring, int>& b) {
            return (a.first < b.first);
        }
    };

    struct amountDescending
    {
        inline bool operator() (const pair<std::wstring, int> &a, const pair<std::wstring, int> &b) {
            return (a.second > b.second);
        }
    };
    
};


#endif //OTIK_ANALYZER_ANALYZER_H
