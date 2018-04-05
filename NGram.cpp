//
// Created by Petr Stenin on 30/03/2018.
//

#include "NGram.h"

int NGram::N;

NGram::NGram() {}

int NGram::n_gram_distance(const std::string &cand_w, const std::string &dict_w) {

    int res = 0, cmn = 0;
    unsigned long i;
    auto *cnd_sbst = new std::vector<std::string>;
    auto *dct_sbst = new std::vector<std::string>;

    std::string cnd = " " + cand_w + " ";
    std::string dct = " " + dict_w + " ";


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

/*
void NGram::get_options(WordCase &word_case, const std::vector<std::string> *dict) {
    int max_dst = std::numeric_limits<int>::max();
    int temp_dst;
    std::vector<std::string> *word_msspl_s = split_word(word_case.getMisspell_w());

    for(std::string w_dict : *dict) {

        // Legacy code
        //temp_dst = n_gram_distance(word_case.getMisspell_w(), w_dict);
        std::vector<std::string> *word_dict_s = split_word(w_dict);
        temp_dst = n_gram_distance_fast(word_msspl_s, word_dict_s);

        if (temp_dst < max_dst) {
            word_case.clear_options(gcnst::NGRAM);
            word_case.add_option(w_dict, gcnst::NGRAM);
            max_dst = temp_dst;
        } else if (temp_dst == max_dst) {
            word_case.add_option(w_dict, gcnst::NGRAM);
        }
        delete(word_dict_s);
    }
    delete(word_msspl_s);
}
 */
void NGram::get_options(WordCase &word_case, const std::vector<std::vector<std::string>*> *dict_ngr_sort,
                        const std::vector<std::string> *dict) {
    int max_dst = std::numeric_limits<int>::max();
    int temp_dst, i;
    std::vector<std::string> *word_msspl_s = split_word(word_case.getMisspell_w());

    for(i = 0; i < dict->size(); ++i) {

        std::vector<std::string> *dict_ws = (*dict_ngr_sort)[i];
        // Legacy code
        //temp_dst = n_gram_distance(word_case.getMisspell_w(), w_dict);

        temp_dst = n_gram_distance_fast(word_msspl_s, dict_ws);

        if (temp_dst < max_dst) {
            word_case.clear_options(gcnst::NGRAM);
            word_case.add_option((*dict)[i], gcnst::NGRAM);
            max_dst = temp_dst;
        } else if (temp_dst == max_dst) {
            word_case.add_option((*dict)[i], gcnst::NGRAM);
        }

    }
    delete(word_msspl_s);
}

std::vector<std::string> *NGram::split_word(const std::string &wrd) {
    auto n_set = new std::vector<std::string>;
    std::string wrd_ext = " " + wrd + " ";
    int i;

    for (i = 0; i < wrd_ext.length() - N + 1; ++i) {
        n_set->push_back(wrd_ext.std::string::substr(i, (unsigned long)N) );
    }


    std::sort(n_set->begin(), n_set->end());
    return n_set;
}

// Input already sorted
int NGram::n_gram_distance_fast(const std::vector<std::string> *cand_ws, const std::vector<std::string> *dict_ws) {
    int cand_ws_sz = cand_ws->size();
    int dict_ws_sz = dict_ws->size();
    int dist = cand_ws_sz + dict_ws_sz;
    int mtch = 0;
    int i = 0, j = 0;
    while (i < cand_ws_sz && j < dict_ws_sz) {
        if ((*cand_ws)[i] == (*dict_ws)[j]) {
            ++mtch;
            ++i;
            ++j;
        } else if ((*cand_ws)[i] > (*dict_ws)[j]) {
            ++j;
        } else {
            ++i;
        }
    }

    return dist - 2*mtch;
}

void NGram::setN(int n) {
    NGram::N = n;
}

int NGram::getN() {
    return N;
}