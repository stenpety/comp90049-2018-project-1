//
// Created by Petr Stenin on 30/03/2018.
//

#include "NGram.h"

int NGram::N;

NGram::NGram() {}

int NGram::n_gram_distance(std::string cnd, std::string dct) {

    int res = 0, cmn = 0;
    unsigned long i;
    auto *cnd_sbst = new std::vector<std::string>;
    auto *dct_sbst = new std::vector<std::string>;

    cnd = " " + cnd + " ";
    dct = " " + dct + " ";


    for (i = 0; i < cnd.length()- N + 1; ++i) {
        cnd_sbst->push_back(cnd.std::string::substr(i, (unsigned long)N) );
    }

    for (i = 0; i < dct.length()- N + 1; ++i) {
        dct_sbst->push_back(dct.std::string::substr(i, (unsigned long)N) );
    }
    res += (cnd_sbst->size() + dct_sbst->size());

    std::vector<std::string>::iterator cnd_sbst_it;
    std::vector<std::string>::iterator dct_sbst_it;
    for (cnd_sbst_it = cnd_sbst->begin(); cnd_sbst_it != cnd_sbst->end(); ++cnd_sbst_it) {
        for (dct_sbst_it = dct_sbst->begin(); dct_sbst_it != dct_sbst->end(); ++dct_sbst_it) {
            if (*cnd_sbst_it == *dct_sbst_it) {
                ++cmn;
                dct_sbst->erase(dct_sbst_it);
                break;
            }
        }
    }

    res -= (2 * cmn);

    delete(cnd_sbst);
    delete(dct_sbst);
    return res;
}

void NGram::get_options(WordCase &word_case, const std::vector<std::string> *dict) {
    int max_dst = std::numeric_limits<int>::max();
    int temp_dst;

    for(std::string w_dict : *dict) {
        temp_dst = n_gram_distance(word_case.getMisspell_w(), w_dict);
        if (temp_dst < max_dst) {
            word_case.clear_options(gcnst::NGRAM);
            word_case.add_option(w_dict, gcnst::NGRAM);
            max_dst = temp_dst;
        } else if (temp_dst == max_dst) {
            word_case.add_option(w_dict, gcnst::NGRAM);
        }
    }
}

void NGram::setN(int n) {
    NGram::N = n;
}