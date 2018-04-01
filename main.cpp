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

    ifstream fmisspell (gcnst::GConst::ADDR_MSSPL.c_str());
    ifstream fcorrect (gcnst::GConst::ADDR_CRCT.c_str());

    WordCase temp = WordCase();

    while (getline(fmisspell, ln_misspell)) {
        getline(fcorrect, ln_correct);
        temp.setMisspell_w(ln_misspell);
        temp.setCorrect_w(ln_correct);
        cases_db->push_back(temp);
    }


    // for test
    cout << "n-th pair: " << (*cases_db)[100].toString() << endl;


    delete(cases_db);

    return 0;
}