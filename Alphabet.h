//
// Created by Grigory on 02/10/2022.
//

#ifndef OTIK_ANALYZER_ALPHABET_H
#define OTIK_ANALYZER_ALPHABET_H

#include <map>
#include <utility>

enum Alphabet{
    BYTE,
    UTF8
};

const std::map<Alphabet, std::pair<int, int>> AlphabetMap = {{BYTE, {1, 256}},
                                                             {UTF8, {4, 1112064}}};

#endif //OTIK_ANALYZER_ALPHABET_H
