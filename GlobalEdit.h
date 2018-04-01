//
// Created by Petr Stenin on 30/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_GLOBALEDIT_H
#define COMP90049_2018_PROJECT_1_GLOBALEDIT_H

#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include "WordCase.h"

#define MATCH_C 1
#define INSERT_C (-1)
#define DELETE_C (-1)
#define REPLACE_C (-1)

class GlobalEdit {
private:
    static int edit_distance(const std::string &, const std::string &, bool);
public:
    static void get_options(WordCase &, const char*);


};


#endif //COMP90049_2018_PROJECT_1_GLOBALEDIT_H
