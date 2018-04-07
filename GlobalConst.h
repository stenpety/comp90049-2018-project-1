//
// Created by Petr Stenin on 31/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_GLOBALCONST_H
#define COMP90049_2018_PROJECT_1_GLOBALCONST_H

#include <string>
#include <fstream>
#include <iostream>

#define NOLIM_CODE (-9999)

namespace gcnst {
    enum Methods {GED, LED, NGRAM, SNDX};

    class GConst {

    public:
        static std::string addr_msspl;
        static std::string addr_crct;
        static std::string addr_dict;

        GConst();

        /**
         * Configures parameters:
         * misspell, correct and dictionary files addresses
         * GED, N-Gram and Soundex options
         */
        static void config(const char *);
    };
}

#include "GlobalEdit.h"
#include "NGram.h"
#include "Soundex.h"

#endif //COMP90049_2018_PROJECT_1_GLOBALCONST_H
