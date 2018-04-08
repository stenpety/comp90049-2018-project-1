//
// Created by Petr Stenin on 30/03/2018.
//

#include "NGram.h"

int NGram::N;
int NGram::score_lim;
double NGram::dice_th;

NGram::NGram() = default;

void NGram::setNgramParms(int N, int score_lim, double dice_th) {
    NGram::N = N;
    NGram::score_lim = score_lim;
    NGram::dice_th = dice_th;
}

int NGram::getN() {
    return N;
}

int NGram::getScore_lim() {
    return score_lim;
}

double NGram::getDice_th() {
    return dice_th;
}

// Legacy code
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

void NGram::get_options(WordCase &word_case, const std::vector<std::vector<std::string>*> *dict_ngr_sort,
                        const std::vector<std::string> *dict) {
    //int min_score = score_lim == NOLIM_CODE ? std::numeric_limits<int>::max() : score_lim;
    //int temp_score;
    double max_dice_sim = dice_th;
    double temp_dice_sim;
    std::vector<std::string> *word_msspl_s = split_word(word_case.getMisspell_w());
    int i;

    for(i = 0; i < dict->size(); ++i) {

        std::vector<std::string> *dict_ws = (*dict_ngr_sort)[i];

        // For use with Dice similarity
        temp_dice_sim = n_gram_dice(word_msspl_s, dict_ws);

        if (temp_dice_sim > max_dice_sim) {
            std::vector<std::string> temp = *word_case.getNgram_opts();
            word_case.clear_options(gcnst::NGRAM);
            word_case.add_option((*dict)[i], gcnst::NGRAM);
            max_dice_sim = temp_dice_sim;

            for (const std::string tmp : temp) {
                std::vector<std::string> *tmp_s = split_word(tmp);
                double temp_d = n_gram_dice(word_msspl_s, tmp_s);

                if (max_dice_sim - temp_d <= DICE_RNG) {
                    word_case.add_option(tmp, gcnst::NGRAM);
                }
                delete(tmp_s);
                tmp_s = nullptr;
            }


        } else if (max_dice_sim-temp_dice_sim <= DICE_RNG) {
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
        n_set->push_back(wrd_ext.std::string::substr(static_cast<unsigned long>(i), (unsigned long)N) );
    }


    std::sort(n_set->begin(), n_set->end());
    return n_set;
}

// Input already sorted
int NGram::n_gram_distance_fast(const std::vector<std::string> *cand_ws, const std::vector<std::string> *dict_ws) {

    unsigned long cand_ws_sz = cand_ws->size();
    unsigned long  dict_ws_sz = dict_ws->size();
    unsigned long mtch = 0;
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

    return cand_ws_sz + dict_ws_sz - 2*mtch;
}

double NGram::n_gram_dice(const std::vector<std::string> *cand_ws, const std::vector<std::string> *dict_ws) {

    int cand_ws_sz = cand_ws->size();
    int dict_ws_sz = dict_ws->size();
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

    return (2 * (double)mtch) / (cand_ws_sz + dict_ws_sz);
}

