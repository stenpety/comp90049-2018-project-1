//
// Created by Petr Stenin on 30/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_SOUNDEX_H
#define COMP90049_2018_PROJECT_1_SOUNDEX_H

#include <string>
#include "WordCase.h"

class WordCase;

class Soundex {
private:
    static const int TRUNC_TO = 4;

public:
    static std::string *sndx_convert(const std::string &);
    static void get_options_exact(WordCase &, const std::vector<std::string> *);
};


#endif //COMP90049_2018_PROJECT_1_SOUNDEX_H
