//
// Created by Grigory on 02/10/2022.
//

#include "functions.h"

string getFileName(const string& filename) {
    return filename.substr(filename.find_last_of("\\") + 1, filename.size());
}

Alphabet getAlphabetFromString(char* str){
    if(strcmp(str,"--byte")==0) {return BYTE; }
    if(strcmp(str,"--utf8")==0) {return UTF8; }
    //scalable
}
