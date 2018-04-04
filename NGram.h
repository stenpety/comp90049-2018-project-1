//
// Created by Petr Stenin on 30/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_NGRAM_H
#define COMP90049_2018_PROJECT_1_NGRAM_H

#include <string>
#include <vector>
#include <limits>
#include "WordCase.h"

//#define N 3

class WordCase;

class NGram {
private:
    static int N;
    static int n_gram_distance(const std::string &, const std::string &);
public:
    NGram();

    static void get_options(WordCase &, const std::vector<std::string> *);

    static void setN(int n);
};


#endif //COMP90049_2018_PROJECT_1_NGRAM_H
