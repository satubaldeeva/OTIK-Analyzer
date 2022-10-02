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
    vector<pair<vector<char>, int>> symbols;
    string file;
    string info_file; //todo ?

public:

    Analyzer(const string& file, Alphabet alphabet_type);
    void processFile();

    static bool testSymbol(const vector<char>&){
       //todo  testSymbol function
        return true;
    }
};


#endif //OTIK_ANALYZER_ANALYZER_H
