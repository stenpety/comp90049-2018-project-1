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

void WordCase::add_option(const std::string add_w, gcnst::Methods method) {
    switch (method) {
        case gcnst::GED:
            ged_opts->push_back(add_w);
            break;
        case gcnst::LED:
            break; // not implemented yet
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
        case gcnst::LED:
            break; // not implemented yet
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

double WordCase::update_precision(gcnst::Methods method) {
    unsigned long words_sz = 0;
    bool found = false;
    double new_prec = 0;
    switch (method) {
        case gcnst::GED:
            words_sz = ged_opts->size();
            found = std::find(ged_opts->begin(), ged_opts->end(), correct_w) != ged_opts->end();
            break;
        case gcnst::LED:
            break; // not implemented yet
        case gcnst::NGRAM:
            words_sz = ngram_opts->size();
            found = std::find(ngram_opts->begin(), ngram_opts->end(), correct_w) != ngram_opts->end();
            break;
        case gcnst::SNDX:
            words_sz = sndx_opts->size();
            found = std::find(sndx_opts->begin(), sndx_opts->end(), correct_w) != sndx_opts->end();
            break;
        default:
            break;
    }

    if (found) {
        new_prec = 1.0 / words_sz;
    }

    return new_prec;
}

double WordCase::getGed_precision() {
    ged_precision = update_precision(gcnst::GED);
    return ged_precision;
}

double WordCase::getNgram_precision() {
    ngram_precision = update_precision(gcnst::NGRAM);
    return ngram_precision;
}

double WordCase::getSndx_precision() {
    sndx_precision = update_precision(gcnst::SNDX);
    return sndx_precision;
}


