//
// Created by Petr Stenin on 31/03/2018.
//

#include "WordCase.h"

WordCase::WordCase() {
    ged_opts = new std::vector<std::string>;
    ged_precision = 0.0;

    ngram_opts = new std::vector<std::string>;
    ngram_precision = 0.0;

    sndx_opts = new std::vector<std::string>;
    sndx_precision = 0.0;
}

WordCase::~WordCase() {
    delete(ged_opts);
    delete(ngram_opts);
    delete(sndx_opts);
}

void WordCase::setCorrect_w(const std::string &correct_w) {
    WordCase::correct_w = correct_w;
}

void WordCase::setMisspell_w(const std::string &misspell_w) {
    WordCase::misspell_w = misspell_w;
}

void WordCase::add_option(std::string add_w, gcnst::Methods method) {
    switch (method) {
        case gcnst::GED:
            ged_opts->push_back(add_w);
            break;
        case gcnst::NGRAM:
            ngram_opts->push_back(add_w);
            break;
        case gcnst::SNDX:
            sndx_opts->push_back(add_w);
            break;
        default:
            break;
    }
}

void WordCase::clear_options(gcnst::Methods method) {
    switch (method) {
        case gcnst::GED:
            ged_opts->clear();
            break;
        case gcnst::NGRAM:
            ngram_opts->clear();
            break;
        case gcnst::SNDX:
            sndx_opts->clear();
            break;
        default:
            break;
    }
}
