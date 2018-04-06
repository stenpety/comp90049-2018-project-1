//
// Created by Petr Stenin on 30/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_NGRAM_H
#define COMP90049_2018_PROJECT_1_NGRAM_H

#include <string>
#include <vector>
#include <limits>

#include "WordCase.h"

class WordCase;

class NGram {
private:
    static int N;
    static int score_lim;
    static int n_gram_distance(const std::string &, const std::string &);
    static int n_gram_distance_fast(const std::vector<std::string> *, const std::vector<std::string> *);
public:
    NGram();

    //static void get_options(WordCase &, const std::vector<std::string> *);
    static void get_options(WordCase &, const std::vector<std::vector<std::string>*> *,
            const std::vector<std::string> *);

    static void setNgramParms(int, int);

    static int getN();

    static int getScore_lim();


    static std::vector<std::string> *split_word(const std::string &);
};


#endif //COMP90049_2018_PROJECT_1_NGRAM_H
