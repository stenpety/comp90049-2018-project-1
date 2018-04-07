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

    /**
     * Converts a string to its Soundex representation
     * @return Soundex string
     */
    static std::string *sndx_convert(const std::string &);

public:

    /**
     * Gets all candidates for a given word from the dictionary
     * Does not return anything
     * Modifies input parameter of WordCase type
     */
    static void get_options_exact(WordCase &, const std::vector<std::string> *);

    static void setTRUNC_TO(int TRUNC_TO);

    static int getTRUNC_TO();
};


#endif //COMP90049_2018_PROJECT_1_SOUNDEX_H
