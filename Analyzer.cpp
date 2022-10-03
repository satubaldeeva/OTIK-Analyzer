//
// Created by Grigory on 02/10/2022.
//

#include "Analyzer.h"

Analyzer::Analyzer(const std::string &file, Alphabet alphabet_type) {
    this->file = file;
    this->symbol_size = alphabet_type;
    this->info_file = file + "_ANALYSIS_INFO.txt";
}

void Analyzer::processFile(){

    FILE* f = fopen(file.c_str(),"rb");
    if(!f)
        cout << "Can't read file " << file << endl;
    else {
        //calculating size
        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        fseek(f, 0, SEEK_SET);


        //reading symbols
        char symbol[symbol_size];

        while (fread(symbol, symbol_size, 1, f) == symbol_size){
            analyzeSymbol(symbol);
        }


    }
    fclose(f);
}

void Analyzer::analyzeSymbol(const char* currentSymbol){
    for(auto & symbol : symbols){
        if(!strcmp(currentSymbol, symbol.first.c_str())){
            //symbol is in the list, so increasing the amount
            symbol.second++;
        }
    }
    //symbol was not found in the list, adding it
    symbols.emplace_back(make_pair(currentSymbol, 1));
}

bool Analyzer::compareNames(const pair<string, int>& a, const pair<string, int>& b) {
    return (a.first < b.first);
}

bool Analyzer::compareAmount(const pair<std::string, int> &a, const pair<std::string, int> &b) {
    return (a.second < b.second);
}