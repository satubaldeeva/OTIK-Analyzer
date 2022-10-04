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

        switch (alphabet) {
            case BYTE:
                //reading symbols
                char byte[1];
                while (fread(byte, 1, 1, f) == 1){
                    analyzeByte(byte);
                    file_size+=1;
                };
                break;
            case UTF8:

            default:
                break;
        }
    }
    fclose(f);
}

void Analyzer::analyzeByte(const char* currentByte){  //todo different for BYTE and UTF-8

    char writeBuff[BUFF_SIZE];
    sprintf(&writeBuff[0], "%02X", currentByte[0]);

    bool found = false;
    for(auto & symbol : symbols){
        if(strcmp(writeBuff, symbol.first.c_str()) == 0){
            //symbol is in the list, so increasing the amount
            symbol.second++;
            found = true;
        }
    }
    if(!found) {
        //symbol was not found in the list, adding it
        symbols.emplace_back(make_pair(writeBuff, 1));
    }

}

void Analyzer::analyzeUTF8(const char* currentSymbol){

}

void Analyzer::makeReportFile() {
    int symbolsInAlphabet = AlphabetMap.find(alphabet)->second.first.second;
    double informationInFile = 0, informationPerSymbol;

    ofstream reportFile(info_file);
    if(!reportFile)
        cout << "Can't open file " << file << endl;
    else {
        reportFile << "FILE: " << file << endl;
        reportFile << "Alphabet: " << AlphabetMap.find(alphabet)->second.second << endl;
        reportFile << "Size (in symbols): " << file_size << endl;
        reportFile << "----------------------------------------"<< endl;
        reportFile << setw(10) << "Symbol" << setw(10) << "Amount" << setw(15) << "Prob" << setw(10) <<"Inform" << endl;

        sort(symbols.begin(), symbols.end(), namesDescending());

        //write for each symbol
        for(auto & symbol : symbols){
            informationPerSymbol = log2(symbolsInAlphabet);
            reportFile << setw(10) << symbol.first << setw(10) << symbol.second << setw(15) <<
            setprecision(3) << (double)1/symbolsInAlphabet << setw(10) << informationPerSymbol << endl;  //todo check formulas
        }
        reportFile << "-----------------------------------------------------------------"<< endl;

        sort(symbols.begin(), symbols.end(), amountDescending());

        //write for each symbol
        for(auto & symbol : symbols){
            informationPerSymbol = log2(symbolsInAlphabet);
            informationInFile += informationPerSymbol;
            reportFile << setw(10) << symbol.first << setw(10) << symbol.second << setw(15)
            <<setprecision(3) << (double)1/symbolsInAlphabet << setw(10) << log2(symbolsInAlphabet) << endl;  //todo check formulas
        }
        reportFile << "-----------------------------------------------------------------"<< endl;
        reportFile << "Amount of information: " << informationInFile << " bytes (" << fixed << setprecision(0)
        << informationInFile*8 << " bits)"
        << endl << endl;

    }


}



