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
    static int TRUNC_TO;

public:
    static std::string *sndx_convert(const std::string &);
    static void get_options_exact(WordCase &, const std::vector<std::string> *);

    static void setTRUNC_TO(int TRUNC_TO);
};


#endif //COMP90049_2018_PROJECT_1_SOUNDEX_H
