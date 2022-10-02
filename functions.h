//
// Created by Grigory on 02/10/2022.
//

#ifndef OTIK_ANALYZER_FUNCTIONS_H
#define OTIK_ANALYZER_FUNCTIONS_H

#include <string>
#include <cstring>

#include "Alphabet.h"
using namespace std;

string getFileName(const string& filename);

Alphabet getAlphabetFromString(char* str);

#endif //OTIK_ANALYZER_FUNCTIONS_H
