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

    if (argc < 3) {
        perror("Error! Not enough parameters. Exiting...");
        exit(EXIT_FAILURE);
    }

    gcnst::GConst::config(argv[1]);

    ifstream fmisspell (gcnst::GConst::addr_msspl.c_str());
    ifstream fcorrect (gcnst::GConst::addr_crct.c_str());

    WordCase temp = WordCase();

    while (getline(fmisspell, ln_misspell)) {
        getline(fcorrect, ln_correct);
        temp.setMisspell_w(ln_misspell);
        temp.setCorrect_w(ln_correct);
        cases_db->push_back(temp);
    }

    ifstream fdict (gcnst::GConst::addr_dict.c_str());
    while (getline(fdict, ln_dict)) {
        dict->push_back(ln_dict);
    }

    //NGram::setN(3);

    // Output text file
    ofstream foutput (argv[2]);


    for (WordCase w_case : (*cases_db)) {
        foutput << "\nn-th pair: " << w_case.toString() << endl;
        GlobalEdit::get_options(w_case, dict);
        NGram::get_options(w_case, dict);


        foutput << "Ged opts:" << endl;
        for (const string &tmp : *(w_case.getGed_opts()) ) {
            foutput << tmp << " ";
        }
        foutput << endl;


        foutput << "N-Gram opts:" <<endl;
        for (string tmp : *(w_case.getNgram_opts()) ) {
            foutput << tmp << " ";
        }
        foutput << endl;


    }


    /*
    WordCase w_case = (*cases_db)[0];
    cout << "n-th pair: " << w_case.toString() << endl;
    GlobalEdit::get_options(w_case,gcnst::GConst::ADDR_DICT.c_str());


    for (string tmp : (*(*cases_db)[1].getGed_opts())) {
        cout << tmp << endl;
    }
     */


    // Close files
    fmisspell.close();
    fcorrect.close();
    fdict.close();
    foutput.close();

    // Free memory
    delete(cases_db);
    delete(dict);

    return 0;
}