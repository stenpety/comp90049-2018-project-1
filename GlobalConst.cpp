//
// Created by Petr Stenin on 01/04/2018.
//

#include "GlobalConst.h"

using namespace gcnst;

std::string GConst::addr_msspl;
std::string GConst::addr_crct;
std::string GConst::addr_dict;

GConst::GConst() = default;

void GConst::config(const char *addr_conf) {

    int match_c, insert_c, delete_c, replace_c, dist_limit;
    int ngram_n, ngram_score_lim;
    double ngram_dice_th;
    int sndx_trunc;
    std::string temp;

    std::ifstream fconfig (addr_conf);

    getline(fconfig, addr_msspl);
    getline(fconfig, addr_crct);
    getline(fconfig, addr_dict);


    getline(fconfig, temp);
    match_c = atoi(temp.c_str());
    getline(fconfig, temp);
    insert_c = atoi(temp.c_str());
    getline(fconfig, temp);
    delete_c = atoi(temp.c_str());
    getline(fconfig, temp);
    replace_c = atoi(temp.c_str());
    getline(fconfig, temp);
    dist_limit = atoi(temp.c_str());
    GlobalEdit::set_edit_parms(match_c, insert_c, delete_c, replace_c, dist_limit);

    getline(fconfig, temp);
    ngram_n = atoi(temp.c_str());
    getline(fconfig, temp);
    ngram_score_lim = atoi(temp.c_str());
    getline(fconfig, temp);
    ngram_dice_th = atof(temp.c_str()); //!!!
    NGram::setNgramParms(ngram_n, ngram_score_lim, ngram_dice_th);

    getline(fconfig, temp);
    sndx_trunc = atoi(temp.c_str());
    Soundex::setTRUNC_TO(sndx_trunc);

    std::cout << "Configuration done!" << std::endl;
    fconfig.close();
}