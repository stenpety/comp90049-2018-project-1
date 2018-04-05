//
// Created by Petr Stenin on 30/03/2018.
//

#include "GlobalEdit.h"

int GlobalEdit::MATCH_C = 1;
int GlobalEdit::INSERT_C = -1;
int GlobalEdit::DELETE_C = -1;
int GlobalEdit::REPLACE_C = -1;

int GlobalEdit::dist_limit = 0;

static int dist_limit;


void GlobalEdit::set_edit_parms(int match_c, int insert_c, int delete_c, int replace_c, int dist_limit) {
    MATCH_C = match_c;
    INSERT_C = insert_c;
    DELETE_C = delete_c;
    REPLACE_C = replace_c;

    GlobalEdit::dist_limit = dist_limit;
}

int GlobalEdit::edit_distance(const std::string &cand_w, const std::string &dict_w, bool global) {
    int i, j, temp;
    int ins_c, del_c, mtc_c, rpl_c;
    int res;
    auto table = new std::vector<std::vector<int>>;
    auto temp_row = new std::vector<int>;
    std::string cnd = cand_w;
    std::string dct = dict_w;
    cnd = " " + cnd;
    dct = " " + dct;

    unsigned long cnd_len = cnd.length();
    unsigned long dct_len = dct.length();

    // top row
    temp_row->push_back(0);
    for (j = 1; j < cnd_len; ++j) {
        temp_row->push_back(global ? (*temp_row)[j-1] + DELETE_C : 0);
    }
    table->push_back(*temp_row);
    temp_row->clear();

    // left column
    for (i = 1; i < dct_len; ++i) {

        temp_row->push_back(global ? (*table)[i-1][0] + INSERT_C : 0);


        for (j = 1; j < cnd_len; ++j) {
            ins_c = (*table)[i-1][j] + INSERT_C;
            del_c = (*temp_row)[j-1] + DELETE_C;
            rpl_c = (*table)[i-1][j-1] + REPLACE_C;
            mtc_c = (*table)[i-1][j-1] + MATCH_C;

            if (cnd[j] == dct[i]) {
                temp = std::max(std::max(ins_c,del_c),std::max(rpl_c,mtc_c));
            } else {
                temp =  std::max(std::max(ins_c,del_c),rpl_c);
            }
            temp_row->push_back(global ? temp : std::max(temp,0));
        }
        table->push_back(*temp_row);
        temp_row->clear();
    }

    /*
    for (i = 0; i < dct_len; ++i) {
        for (j = 0; j < cnd_len; ++j) {
            printf("%2d ", (*table)[i][j]);
        }
        printf("\n");
    }
     */

    res = (*table)[dct_len-1][cnd_len-1];

    delete(table);
    delete(temp_row);
    return res;
}


int GlobalEdit::edit_distance_fast(const std::string &cand_w, const std::string &dict_w, bool) {
    int i, j, temp;
    int ins_c, del_c, mtc_c, rpl_c;

    std::vector<int> prev_row, curr_row;
    prev_row.push_back(0);
    for (j = 0; j < cand_w.length(); ++j) {
        prev_row.push_back(prev_row.back()+DELETE_C);
    }

    for (i = 0; i < dict_w.length(); ++i) {
        curr_row.push_back(prev_row.front()+INSERT_C);
        for (j = 0; j < cand_w.length(); ++j) {
            ins_c = prev_row[j+1] + INSERT_C;
            del_c = curr_row.back() + DELETE_C;
            rpl_c = prev_row[j] + REPLACE_C;
            mtc_c = prev_row[j] + MATCH_C;
            if (cand_w[j] == dict_w[i]) {
                temp = std::max(std::max(ins_c,del_c),std::max(rpl_c,mtc_c));
            } else {
                temp =  std::max(std::max(ins_c,del_c),rpl_c);
            }
            curr_row.push_back(temp);
        }

        prev_row = curr_row;
        curr_row.clear();
    }

    return prev_row[cand_w.length()];
}

void GlobalEdit::get_options(WordCase &word_case, const std::vector<std::string> *dict) {
    int max_dst = std::numeric_limits<int>::min();
    int temp_dst;

    for(std::string w_dict : *dict) {
        temp_dst = edit_distance_fast(word_case.getMisspell_w(), w_dict, true);
        if (temp_dst > max_dst) {
            word_case.clear_options(gcnst::GED);
            word_case.add_option(w_dict, gcnst::GED);
            max_dst = temp_dst;
        } else if (temp_dst == max_dst) {
            word_case.add_option(w_dict, gcnst::GED);
        }
    }

}


