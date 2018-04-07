//
// Created by Petr Stenin on 30/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_GLOBALEDIT_H
#define COMP90049_2018_PROJECT_1_GLOBALEDIT_H

#include <string>
#include <vector>
#include <limits>

#include "WordCase.h"

class WordCase;

class GlobalEdit {
private:
    static int MATCH_C; // cost of match
    static int INSERT_C; // cost of insert
    static int DELETE_C; // cost of delete
    static int REPLACE_C; // cost of replace

    static int dist_limit;

    // Legacy code
    static int edit_distance(const std::string &, const std::string &, bool);

    /**
     * Calculates Global Edit distance for the given pair of words
     * @return edit distance
     */
    static int edit_distance_fast(const std::string &, const std::string &, bool);

public:
    static void set_edit_parms(int, int, int, int, int);

    /**
     * Gets all candidates for a given word from the dictionary
     * Does not return anything
     * Modifies input parameter of WordCase type
     */
    static void get_options(WordCase &, const std::vector<std::string> *);

    static int getMATCH_C();

    static int getINSERT_C();

    static int getDELETE_C();

    static int getREPLACE_C();

    static int getDist_limit();
};


#endif //COMP90049_2018_PROJECT_1_GLOBALEDIT_H
