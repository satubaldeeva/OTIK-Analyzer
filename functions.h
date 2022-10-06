//
// Created by Grigory on 02/10/2022.
//

#ifndef OTIK_ANALYZER_FUNCTIONS_H
#define OTIK_ANALYZER_FUNCTIONS_H

#include <string>
#include <cstring>
#include <iostream>
#include <exception>
#include <vector>

#include "Alphabet.h"
using namespace std;

Alphabet getAlphabetFromString(char* str);

void printUsage();

//devide string into UTF8 substrings (single char)
vector<string> divideString(const string& text);

#endif //OTIK_ANALYZER_FUNCTIONS_H
