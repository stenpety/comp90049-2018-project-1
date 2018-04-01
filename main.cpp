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
    //gcnst::GConst gconst;


    ifstream fmisspell ("/Users/stenpety/test/knowtech/misspell.txt");//(gconst.ADDR_MSSPL.c_str());
    ifstream fcorrect ("/Users/stenpety/test/knowtech/correct.txt");//(gconst.ADDR_CRCT.c_str());


    while (getline(fmisspell, ln_misspell)) {
        getline(fcorrect, ln_correct);
        WordCase temp = WordCase(ln_misspell, ln_correct);
        cout << temp.toString() << endl;
        cases_db->push_back(temp);

    }

    cout << "100th element: " << (*cases_db)[100].getMisspell_w() << " " << (*cases_db)[100].getCorrect_w() << endl;



    delete(cases_db);

    return 0;
}