//
// Created by Grigory on 02/10/2022.
//

#include <fstream>
#include "Analyzer.h"

Analyzer::Analyzer(const std::string &file, Alphabet alphabet_type) {
    this->file = file;
    this->alphabet = alphabet_type;
    this->info_file = file + "_ANALYSIS_INFO.txt";
    this->file_size = 0;
}

void Analyzer::processFile(){

    FILE* f = fopen(file.c_str(),"rb");
    if(!f)
        cout << "Can't read file " << file << endl;
    else {
        //reading symbols
        int symbol_size = AlphabetMap.find(alphabet)->second.first;
        char symbol[symbol_size];

        while (fread(symbol, symbol_size, 1, f) == symbol_size){
            analyzeSymbol(symbol);
            file_size+=1;
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

void Analyzer::makeReportFile() {
    int symbolsInAlphabet = AlphabetMap.find(alphabet)->second.second;
    double informationInFile = 0, informationPerSymbol;

    ofstream reportFile(info_file);
    if(!reportFile)
        cout << "Can't open file " << file << endl;
    else {
        reportFile << "FILE: " << file << endl;
        reportFile << "Alphabet: " << to_string(alphabet) << endl;
        reportFile << "Size (in symbols): " << file_size << endl;
        reportFile << "----------------------------------------"<< endl;
        reportFile << left<< setw(10) << "Symbol" << setw(6) << "Amount" << setw(8) << "Prob" << setw(6) <<"Inform" << endl;

        sort(symbols.begin(), symbols.end(), namesDescending());

        //write for each symbol
        for(auto & symbol : symbols){
            informationPerSymbol = log2(symbolsInAlphabet);
            reportFile << left<< setw(10) << symbol.first << setw(6) << symbol.second << setw(8)
            << 1/symbolsInAlphabet << setw(6) << informationPerSymbol << endl;  //todo check formulas
        }
        reportFile << "-----------------------------------------------------------------"<< endl;

        sort(symbols.begin(), symbols.end(), amountDescending());

        //write for each symbol
        for(auto & symbol : symbols){
            informationPerSymbol = log2(symbolsInAlphabet);
            informationInFile += informationPerSymbol;
            reportFile << left<< setw(10) << symbol.first << setw(6) << symbol.second << setw(8)
                       << 1/symbolsInAlphabet << setw(6) << log2(symbolsInAlphabet) << endl;  //todo check formulas
        }
        reportFile << "-----------------------------------------------------------------"<< endl;
        reportFile << "Amount of information: " << informationInFile << "bytes (" << informationInFile*8 << " bits)"
        << endl << endl;

    }


}



