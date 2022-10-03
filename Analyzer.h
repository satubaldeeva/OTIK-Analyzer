//
// Created by Grigory on 02/10/2022.
//

#ifndef OTIK_ANALYZER_ANALYZER_H
#define OTIK_ANALYZER_ANALYZER_H

#include <vector>
#include <utility>
#include <string>
#include <iostream>

#include "functions.h"

using namespace std;

class Analyzer {
private:
    vector<pair<string, int>> symbols;
    string file;
    int symbol_size;
    string info_file; //todo ?

public:

    Analyzer(const string& file, Alphabet alphabet_type);
    void processFile();
    void analyzeSymbol(const char*);

    //comparators to sort symbols array
    bool compareNames(const pair<string, int>& a, const pair<string, int>& b);
    bool compareAmount(const pair<string, int>& a, const pair<string, int>& b);
};


#endif //OTIK_ANALYZER_ANALYZER_H
