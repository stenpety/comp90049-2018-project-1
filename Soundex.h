//
// Created by Petr Stenin on 30/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_SOUNDEX_H
#define COMP90049_2018_PROJECT_1_SOUNDEX_H

#include <string>

class Soundex {
private:
    static const int TRUNC_TO = 4;

public:
    std::string *sndx_convert(std::string);
};


#endif //COMP90049_2018_PROJECT_1_SOUNDEX_H
