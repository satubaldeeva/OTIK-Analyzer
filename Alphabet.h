//
// Created by Grigory on 02/10/2022.
//

#ifndef OTIK_ANALYZER_ALPHABET_H
#define OTIK_ANALYZER_ALPHABET_H

#include <map>
#include <utility>
#include <string>

enum Alphabet{
    BYTE,
    UTF8
};

const std::map<Alphabet, std::pair<std::pair<int, int>, std::string>> AlphabetMap =
        {{BYTE, {{1, 256}, "BYTE"}},
         {UTF8, {{4, 1112064}, "UTF8"}}};

#endif //OTIK_ANALYZER_ALPHABET_H
