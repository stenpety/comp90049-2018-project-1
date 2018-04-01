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


    string ln_misspell, ln_correct;

    auto cases_db = new vector<WordCase>;

    ifstream fmisspell (gcnst::GConst::ADDR_MSSPL_SHRT.c_str());
    ifstream fcorrect (gcnst::GConst::ADDR_CRCT_SHRT.c_str());

    WordCase temp = WordCase();

    while (getline(fmisspell, ln_misspell)) {
        getline(fcorrect, ln_correct);
        temp.setMisspell_w(ln_misspell);
        temp.setCorrect_w(ln_correct);
        cases_db->push_back(temp);
    }


    // for test
    /*
    for (WordCase w_case : (*cases_db)) {
        cout << "n-th pair: " << w_case.toString() << endl;
        GlobalEdit::get_options(w_case,gcnst::GConst::ADDR_DICT.c_str());


        for (string tmp : (*(*cases_db)[1].getGed_opts())) {
            cout << tmp << endl;
        }

    }
     */
    /*
    WordCase w_case = (*cases_db)[0];
    cout << "n-th pair: " << w_case.toString() << endl;
    GlobalEdit::get_options(w_case,gcnst::GConst::ADDR_DICT.c_str());


    for (string tmp : (*(*cases_db)[1].getGed_opts())) {
        cout << tmp << endl;
    }
     */


    delete(cases_db);

    return 0;
}