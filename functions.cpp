//
// Created by Grigory on 02/10/2022.
//

#include "functions.h"

string getFileName(const string& filename) {
    return filename.substr(filename.find_last_of("\\") + 1, filename.size());
}

Alphabet getAlphabetFromString(char* str){
    //todo  getAlphabetFromString function
}
