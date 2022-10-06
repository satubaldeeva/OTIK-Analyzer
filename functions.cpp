//
// Created by Grigory on 02/10/2022.
//

#include <locale>
#include <codecvt>
#include "functions.h"

Alphabet getAlphabetFromString(char* str){
    if(strcmp(str,"--byte")==0) {return BYTE; }
    if(strcmp(str,"--utf8")==0) {return UTF8; }
    throw invalid_argument("Invalid argument key");
}

void printUsage(){
    cout << "USAGE:" << endl;
    cout << "--type  <file to analyze>" << endl;
    cout << "AVALIABLE TYPES:" << endl;
    cout << "* byte\n* utf8" << endl;
}

vector<string> divideString(const string& text){
    vector<string> array;
    for(size_t i = 0; i < text.length();)
    {
        int cplen = 1;
        if((text[i] & 0xf8) == 0xf0) cplen = 4;
        else if((text[i] & 0xf0) == 0xe0) cplen = 3;
        else if((text[i] & 0xe0) == 0xc0) cplen = 2;
        if((i + cplen) > text.length()) cplen = 1;

        array.emplace_back(text.substr(i, cplen));
        i += cplen;
    }
    return array;
}
