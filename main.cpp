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
    int total_wrds = 0;
    int ged_opts_cnt = 0, ged_success = 0;
    int ngram_opts_cnt = 0, ngram_success = 0;
    int sndx_opts_cnt = 0, sndx_success = 0;

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

    NGram::setN(3);

    // Output text file
    ofstream foutput (argv[2]);

    // output to file - tab separated
    for (WordCase w_case : (*cases_db)) {
        foutput << w_case.toString() << "\t";

        GlobalEdit::get_options(w_case, dict);
        ged_opts_cnt += w_case.getGed_opts()->size();
        ged_success += std::find(w_case.getGed_opts()->begin(), w_case.getGed_opts()->end(), w_case.getCorrect_w())
                       != w_case.getGed_opts()->end() ? 1 : 0;

        NGram::get_options(w_case, dict);
        ngram_opts_cnt += w_case.getNgram_opts()->size();
        ngram_success += std::find(w_case.getNgram_opts()->begin(), w_case.getNgram_opts()->end(), w_case.getCorrect_w())
                       != w_case.getNgram_opts()->end() ? 1 : 0;

        Soundex::get_options_exact(w_case, dict);
        sndx_opts_cnt += w_case.getSndx_opts()->size();
        sndx_success += std::find(w_case.getSndx_opts()->begin(), w_case.getSndx_opts()->end(), w_case.getCorrect_w())
                         != w_case.getSndx_opts()->end() ? 1 : 0;


        for (const string &tmp : *(w_case.getGed_opts()) ) {
            foutput << tmp << " ";
        }
        foutput << "\t" << w_case.getGed_opts()->size() << "\t";

        for (string tmp : *(w_case.getNgram_opts()) ) {
            foutput << tmp << " ";
        }
        foutput << "\t" << w_case.getNgram_opts()->size() << "\t";

        for (string tmp : *(w_case.getSndx_opts()) ) {
            foutput << tmp << " ";
        }
        foutput << "\t" << w_case.getSndx_opts()->size() << endl;

        ++total_wrds;
    }

    foutput << "Total words: " << total_wrds << endl;
    foutput << "GED opts: " << ged_opts_cnt << "\t GED success: " << ged_success << endl;
    foutput << "N-Gram opts: " << ngram_opts_cnt << "\t N-Gram success: " << ngram_success << endl;
    foutput << "Soundex opts: " << sndx_opts_cnt << "\t Soundex success: " << sndx_success << endl;

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