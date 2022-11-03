//
// Created by Grigory on 02/10/2022.
//

#ifndef OTIK_ANALYZER_ANALYZER_H
#define OTIK_ANALYZER_ANALYZER_H

#include <algorithm>
#include <iomanip>
#include <cmath>

#include "functions.h"

#define BUFF_SIZE 10

using namespace std;

class Analyzer {
private:
    vector<pair<string, int>> symbols;
    vector<pair<string, int>> pair_symbols;
    vector<pair<string, int>> pair_start_symbol;
    string file;

    Alphabet alphabet;
    string info_file;
    int file_size;

public:

    Analyzer(const string& file, Alphabet alphabet_type);
    void processFile();
    void analyzeByte(const char* currentByte);
    void analyzeBytePair(const char* currentByte);
    void analyzeByteAllPair();
    void analyzeUTF8(const string& currentSymbol);
    void analyzeUTF8Pair(const string& currentSymbol);
    void analyzeAllPair();
    void makeReportFile();

    //comparators to sort symbols array
    struct namesDescending
    {
        inline bool operator() (const pair<string, int>& a, const pair<string, int>& b) {
            return (a.first < b.first);
        }
    };

    struct amountDescending
    {
        inline bool operator() (const pair<std::string, int> &a, const pair<std::string, int> &b) {
            return (a.second > b.second);
        }
    };
    
};


#endif //OTIK_ANALYZER_ANALYZER_H
