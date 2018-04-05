//
// Created by Petr Stenin on 30/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_GLOBALEDIT_H
#define COMP90049_2018_PROJECT_1_GLOBALEDIT_H

#include <string>
#include <vector>
#include <limits>

#include "WordCase.h"

#define NOLIM_CODE -9999

class WordCase;

class GlobalEdit {
private:
    static int MATCH_C;
    static int INSERT_C;
    static int DELETE_C;
    static int REPLACE_C;

    static int dist_limit;

    static int edit_distance(const std::string &, const std::string &, bool);

public:
    static void set_edit_parms(int, int, int, int, int);
    static void get_options(WordCase &, const std::vector<std::string> *);
    static int edit_distance_fast(const std::string &, const std::string &, bool);

    static int getMATCH_C();

    static int getINSERT_C();

    static int getDELETE_C();

    static int getREPLACE_C();

    static int getDist_limit();
};


#endif //COMP90049_2018_PROJECT_1_GLOBALEDIT_H
