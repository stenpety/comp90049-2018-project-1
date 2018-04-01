//
// Created by Petr Stenin on 31/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_WORDCASE_H
#define COMP90049_2018_PROJECT_1_WORDCASE_H

#include <string>
#include <vector>
#include <iostream>
#include "GlobalConst.h"


class WordCase {
private:
    std::string misspell_w;
    std::string correct_w;

    std::vector<std::string> *ged_opts;
    double ged_precision;

    std::vector<std::string> *ngram_opts;
    double ngram_precision;

    std::vector<std::string> *sndx_opts;
    double sndx_precision;

    double update_precision(gcnst::Methods);

public:
    WordCase();

    ~WordCase();

    void setCorrect_w(const std::string &correct_w);

    void setMisspell_w(const std::string &misspell_w);

    void add_option(std::string, gcnst::Methods);

    void clear_options(gcnst::Methods);

    const std::string &getCorrect_w() const;

    const std::string &getMisspell_w() const;

    double getGed_precision();

    double getNgram_precision();

    double getSndx_precision();

    const std::string toString();

};


#endif //COMP90049_2018_PROJECT_1_WORDCASE_H
