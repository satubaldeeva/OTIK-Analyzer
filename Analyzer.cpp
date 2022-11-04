//
// Created by Grigory on 02/10/2022.
//
#include "string.h"
#include <fstream>
#include "Analyzer.h"/

Analyzer::Analyzer(const std::string &file, Alphabet alphabet_type) {
    this->file = file;
    this->alphabet = alphabet_type;
    this->info_file = file + "_ANALYSIS_INFO.txt";
    this->file_size = 0;
}

void Analyzer::processFile(){

   ifstream f;
   string str;
   vector<string> all_syms;

    f.open(file);
    if(!f)
        cout << "Can't read file " << file << endl;
    else {
        switch (alphabet) {
            case BYTE:
                //reading symbols
                char byte[1];
                while (f.read(byte, 1)){
                    analyzeByte(byte);
                    all_syms.push_back(byte);
                    file_size+=1;
                };

                for(auto & symbol : all_syms){
                    symbol=symbol[0];
                }
                cout<<"print:\n";
                for(auto & symbol : all_syms){
                    cout<<symbol;
                }
                cout<<"------------------------------------------------------\n";
                for(int i = 0; i < all_syms.size()-1; i++){//do pair symbols by index in vector
                    string a = all_syms[i];
                    a.append(all_syms[i+1]);
                    cout<<a<<endl;//пары формируются верно
                    analyzeBytePair(a.c_str());
                }
                analyzeAllPairByte();

              f.close();
                break;

            case UTF8:

                while (getline(f, str)) {
                    vector<string> syms = divideString(str);
                    all_syms.insert(all_syms.end(),syms.begin(),syms.end());
                    for(int i = 0; i < syms.size(); i++){
                        analyzeUTF8(syms[i]);
                        file_size += 1;
                    }

                };
                for(int i = 0; i < all_syms.size()-1; i++){//do pair symbols by index in vector
                    basic_string<char> a =all_syms[i] + all_syms[i+1];
                    analyzeUTF8Pair(a);
                }
                analyzeAllPair();
                f.close();

            default:
                break;
        }
    }



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


void Analyzer::analyzeBytePair(const char* currentByte){  //todo different for BYTE and UTF-8

    char writeBuff[BUFF_SIZE];
    sprintf(&writeBuff[0], "%02X", currentByte[0]);
    sprintf(&writeBuff[2], "%02X", currentByte[1]);
    cout<<writeBuff<<" " <<currentByte[0]<<" "<<currentByte[1]<<"\n";

    bool found = false;
    for(auto & symbol : pair_symbols){
        if(strcmp(writeBuff, symbol.first.c_str()) == 0){
            //symbol is in the list, so increasing the amount
            symbol.second++;
            found = true;
        }
    }
    if(!found) {
        //symbol was not found in the list, adding it
        pair_symbols.emplace_back(make_pair(writeBuff, 1));
    }

}

void Analyzer::analyzeUTF8(const string& currentSymbol){
    bool found = false;
    for(auto & symbol : symbols){
        if(symbol.first == currentSymbol){
            //symbol is in the list, so increasing the amount
            symbol.second++;
            found = true;
        }
    }
    if(!found) {
        //symbol was not found in the list, adding it
        symbols.emplace_back(make_pair(currentSymbol, 1));
    }
}


void Analyzer::analyzeUTF8Pair(const string& currentSymbol){
    bool found = false;
    for(auto & symbol : pair_symbols){
        if(symbol.first == currentSymbol){
            //symbol is in the list, so increasing the amount
            symbol.second++;
            found = true;
        }
    }
    if(!found) {
        //symbol was not found in the list, adding it
        pair_symbols.emplace_back(make_pair(currentSymbol, 1));
    }
}

void Analyzer::analyzeAllPairByte() {

    for (auto &s: symbols) {//create a new vector to count all pairs with this symbol
        pair_start_symbol.emplace_back(make_pair(s.first, 0));
    }
    for (auto &s: pair_start_symbol) {//search pairs
        for (auto &symbol: pair_symbols) {

            if (s.first[0] == symbol.first[0] || s.first[1] == symbol.first[1]) {
                //symbol is in the list, so increasing the amount
                s.second++;
            }
        }
    }
}
void Analyzer::analyzeAllPair(){

    for(auto & s:symbols) {//create a new vector to count all pairs with this symbol
        pair_start_symbol.emplace_back(make_pair(s.first, 0));
    }
    for( auto &s:pair_start_symbol){//search pairs
        for (auto &symbol: pair_symbols) {

            if (*s.first.begin() == *symbol.first.begin()) {
                //symbol is in the list, so increasing the amount
                std::cout<<"symlol from table "<<symbol.first[0]<<symbol.first[2]<<endl;

                s.second++;
            }
        }
    }

}

void Analyzer::makeReportFile() {
    double informationInFile = 0, informationPerSymbol, probability;

    ofstream reportFile(info_file, ios_base::out);
    if(!reportFile)
        cout << "Can't open file " << info_file << endl;
    else {
        reportFile << "FILE: " << file << endl;
        reportFile << "Alphabet: " << alphabetNamingMap.find(alphabet)->second << endl;
        reportFile << "Size (in symbols): " << file_size << endl;
        reportFile << "----------------------------------------"<< endl;
        reportFile << setw(10) << "Symbol" << setw(10) << "Amount" << setw(30) << "Unconditional probability" << endl;

        sort(symbols.begin(), symbols.end(), namesDescending());

        //write for each symbol
        for(auto & symbol : symbols){
            probability = (double)symbol.second/256;//безусловная вероятность
            informationPerSymbol =(double)( -log2(probability));
            reportFile  << setw(10) << symbol.first << setw(10) << symbol.second << setw(30) <<
            setprecision(10) << fixed << probability << setw(10) << setprecision(1) << endl;
            informationInFile +=  symbol.second * informationPerSymbol;
        }
        reportFile << "-----------------------------------------------------------------"<< endl;

        reportFile << setw(10) << "Symbol"<< setw(30) << "Conditional probability"<< endl;
        for(auto & symbol : pair_start_symbol){
            probability = (double)symbol.second/pair_symbols.size();//безусловная вероятность
            informationPerSymbol =(double)(-log2(probability));
            reportFile  << setw(10) << symbol.first << setw(30) <<fixed << setprecision(10)<< probability << endl;
            informationInFile +=  symbol.second * informationPerSymbol;
        }
        reportFile << "-----------------------------------------------------------------"<< endl;
        reportFile << "Amount of information: " << informationInFile/8 << " bytes (" << fixed << setprecision(0)
        << informationInFile << " bits)"
        << endl << endl;
        reportFile << "-----------------------------------------------------------------"<< endl;
        reportFile << "Number of occurrences of substrings"  << endl << endl;
        for(auto & symbol : pair_symbols){

            reportFile  << setw(10) <<"("<< symbol.first<< ")" << setw(10) << symbol.second <<setw(20) <<endl;  //todo check formulas
        }
        reportFile << "-----------------------------------------------------------------"<< endl;
        reportFile << "The common occurrence of any two-character substrings starting with the character"  << endl << endl;

        for(auto & symbol : pair_start_symbol){

            reportFile  << setw(10) << symbol.first << setw(10) << symbol.second <<setw(20) <<endl;  //todo check formulas
        }
    }
    reportFile.close();


}



