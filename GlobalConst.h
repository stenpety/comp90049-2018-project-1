//
// Created by Petr Stenin on 31/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_GLOBALCONST_H
#define COMP90049_2018_PROJECT_1_GLOBALCONST_H

#include <string>

namespace gcnst {
    enum Methods {GED, LED, NGRAM, SNDX};


    class GConst {
    public:
        GConst();

    public:
        static const std::string ADDR_MSSPL;
        static const std::string ADDR_CRCT;
        static const std::string ADDR_DICT;
    };
}


#endif //COMP90049_2018_PROJECT_1_GLOBALCONST_H
