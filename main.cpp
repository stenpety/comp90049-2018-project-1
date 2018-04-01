#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "GlobalConst.h"
#include "GlobalEdit.h"
#include "NGram.h"
#include "Soundex.h"
#include "WordCase.h"

using namespace std;

int main(int argc, char **argv) {


    string ln_misspell, ln_correct, ln_dict;

    auto cases_db = new vector<WordCase>;
    auto dict = new vector<string>;

    ifstream fmisspell (gcnst::GConst::ADDR_MSSPL_SHRT.c_str());
    ifstream fcorrect (gcnst::GConst::ADDR_CRCT_SHRT.c_str());

    WordCase temp = WordCase();

    while (getline(fmisspell, ln_misspell)) {
        getline(fcorrect, ln_correct);
        temp.setMisspell_w(ln_misspell);
        temp.setCorrect_w(ln_correct);
        cases_db->push_back(temp);
    }

    ifstream fdict (gcnst::GConst::ADDR_DICT.c_str());
    while (getline(fdict, ln_dict)) {
        dict->push_back(ln_dict);
    }

    //NGram::setN(3);


    // for test

    for (WordCase w_case : (*cases_db)) {
        cout << "\nn-th pair: " << w_case.toString() << endl;
        GlobalEdit::get_options(w_case, dict);
        NGram::get_options(w_case, dict);

        cout << "Ged opts:" <<endl;
        for (string tmp : *(w_case.getGed_opts()) ) {
            cout << tmp << " ";
        }
        cout << endl;

        cout << "N-Gram opts:" <<endl;
        for (string tmp : *(w_case.getNgram_opts()) ) {
            cout << tmp << " ";
        }
        cout << endl;

        cout << "Prec. GED: "<< w_case.getGed_precision() << "; Prec. N-Gram: " << w_case.getNgram_precision() << endl;
    }

    /*
    WordCase w_case = (*cases_db)[0];
    cout << "n-th pair: " << w_case.toString() << endl;
    GlobalEdit::get_options(w_case,gcnst::GConst::ADDR_DICT.c_str());


    for (string tmp : (*(*cases_db)[1].getGed_opts())) {
        cout << tmp << endl;
    }
     */


    delete(cases_db);
    delete(dict);

    return 0;
}