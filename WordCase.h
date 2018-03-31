//
// Created by Petr Stenin on 31/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_WORDCASE_H
#define COMP90049_2018_PROJECT_1_WORDCASE_H

#include <string>
#include <vector>


class WordCase {
private:
    std::string correct_w;
    std::string misspell_w;

    std::vector<std::string> *ged_opts;
    double ged_precision;

    std::vector<std::string> *ngram_opts;
    double ngram_precision;

    std::vector<std::string> *sndx_opts;
    double sndx_precision;

public:
    WordCase();

    virtual ~WordCase();

    void setCorrect_w(const std::string &correct_w);

    void setMisspell_w(const std::string &misspell_w);

};


#endif //COMP90049_2018_PROJECT_1_WORDCASE_H
