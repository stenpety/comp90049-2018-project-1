//
// Created by Petr Stenin on 30/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_GLOBALEDIT_H
#define COMP90049_2018_PROJECT_1_GLOBALEDIT_H

#include <string>
#include <vector>

#define MATCH_C 1
#define INSERT_C -1
#define DELETE_C -1
#define REPLACE_C -1

class GlobalEdit {

public:
    static int global_distance(std::string cnd, std::string dct);


};


#endif //COMP90049_2018_PROJECT_1_GLOBALEDIT_H
