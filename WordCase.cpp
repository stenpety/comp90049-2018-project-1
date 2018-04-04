//
// Created by Petr Stenin on 31/03/2018.
//

#include "WordCase.h"

WordCase::WordCase() {
    ged_opts = new std::vector<std::string>;
    ged_found = false;

    ngram_opts = new std::vector<std::string>;
    ngram_found = false;

    sndx_opts = new std::vector<std::string>;
    sndx_found = false;
}

WordCase::~WordCase() {
    delete(ged_opts);
    ged_opts = nullptr;

    delete(ngram_opts);
    ngram_opts = nullptr;

    delete(sndx_opts);
    sndx_opts = nullptr;
}

// Copy Constr - Deep copy
WordCase::WordCase(const WordCase &wc):
    misspell_w(wc.misspell_w),
    correct_w(wc.correct_w),
    ged_opts(new std::vector<std::string>),
    ngram_opts(new std::vector<std::string>),
    sndx_opts(new std::vector<std::string>) {
    *ged_opts = *wc.ged_opts;
    *ngram_opts = *wc.ngram_opts;
    *sndx_opts = *wc.ngram_opts;
}

// Asst Op - Deep copy
WordCase &WordCase::operator=(const WordCase &wc) {
    misspell_w = wc.misspell_w;
    correct_w = wc.correct_w;

    ged_opts = new std::vector<std::string>;
    ngram_opts = new std::vector<std::string>;
    sndx_opts = new std::vector<std::string>;

    *ged_opts = *wc.ged_opts;
    *ngram_opts = *wc.ngram_opts;
    *sndx_opts = *wc.ngram_opts;

    return *this;
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

const std::string &WordCase::getCorrect_w() const {
    return correct_w;
}

const std::string & WordCase::getMisspell_w() const {
    return misspell_w;
}


// found = std::find(ged_opts->begin(), ged_opts->end(), correct_w) != ged_opts->end();

const std::string WordCase::toString() {
    return "m: " + misspell_w + "; c: " + correct_w +";";
}

std::vector<std::string> *WordCase::getGed_opts() const {
    return ged_opts;
}

std::vector<std::string> *WordCase::getNgram_opts() const {
    return ngram_opts;
}

std::vector<std::string> *WordCase::getSndx_opts() const {
    return sndx_opts;
}


