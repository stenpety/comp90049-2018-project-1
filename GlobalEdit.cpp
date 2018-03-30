//
// Created by Petr Stenin on 30/03/2018.
//

#include "GlobalEdit.h"

int GlobalEdit::global_distance(std::string cnd, std::string dct) {
    int i, j;
    int ins_c, del_c, mtc_c, rpl_c;
    int res;
    std::vector<std::vector<int>> *table = new std::vector<std::vector<int>>;
    std::vector<int> *temp_row = new std::vector<int>;
    cnd = " " + cnd;
    dct = " " + dct;

    int cnd_len = cnd.length();
    int dct_len = dct.length();

    // top row
    temp_row->push_back(0);
    for (j = 1; j < cnd_len; ++j) {
        temp_row->push_back((*temp_row)[j-1] + DELETE_C);
    }
    table->push_back(*temp_row);
    temp_row->clear();

    //printf("0-0 : %d ", (*table)[i-1][0]);


    // left column
    for (i = 1; i < dct_len; ++i) {

        temp_row->push_back((*table)[i-1][0] + INSERT_C);


        for (j = 1; j < cnd_len; ++j) {
            ins_c = (*table)[i-1][j] + INSERT_C;
            del_c = (*temp_row)[j-1] + DELETE_C;
            rpl_c = (*table)[i-1][j-1] + REPLACE_C;
            mtc_c = (*table)[i-1][j-1] + MATCH_C;

            if (cnd[j] == dct[i]) {
                temp_row->push_back( std::max(std::max(ins_c,del_c),std::max(rpl_c,mtc_c) ) );
            } else {
                temp_row->push_back( std::max(std::max(ins_c,del_c),rpl_c ) );
            }

        }
        table->push_back(*temp_row);
        temp_row->clear();
    }

    for (i = 0; i < dct_len; ++i) {
        for (j = 0; j < cnd_len; ++j) {
            printf("%d ", (*table)[i][j]);
        }
        printf("\n");
    }

    res = (*table)[dct_len-1][cnd_len-1];

    delete(table);
    delete(temp_row);
    return res;
}