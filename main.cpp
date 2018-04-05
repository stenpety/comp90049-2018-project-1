#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

#include "GlobalConst.h"
#include "WordCase.h"

using namespace std;



int main(int argc, char **argv) {


    string ln_misspell, ln_correct, ln_dict;
    int total_wrds = 0;
    int ged_opts_cnt = 0, ged_success = 0;
    int ngram_opts_cnt = 0, ngram_success = 0;
    int sndx_opts_cnt = 0, sndx_success = 0;

    time_t timer_start = clock();

    auto cases_db = new vector<WordCase>;
    auto dict = new vector<string>;
    auto dict_ngr_sort = new vector<vector<string>*>;

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
        dict_ngr_sort->push_back(NGram::split_word(ln_dict));
    }

    // Output text file
    ofstream foutput (argv[2]);

    // Table heading
    foutput << "Misspelled" << "\t" << "Correct" << "\t" << "GED" << "\t" << "N-Gr" << "\t" << "Sndx" << endl;

    // output to file - tab separated
    for (WordCase w_case : (*cases_db)) {
        foutput << w_case.toString() << "\t";

        //GlobalEdit::get_options(w_case, dict);
        ged_opts_cnt += w_case.getGed_opts()->size();
        ged_success += std::find(w_case.getGed_opts()->begin(), w_case.getGed_opts()->end(), w_case.getCorrect_w())
                       != w_case.getGed_opts()->end() ? 1 : 0;

        NGram::get_options(w_case, dict_ngr_sort, dict);
        ngram_opts_cnt += w_case.getNgram_opts()->size();
        ngram_success += std::find(w_case.getNgram_opts()->begin(), w_case.getNgram_opts()->end(), w_case.getCorrect_w())
                       != w_case.getNgram_opts()->end() ? 1 : 0;

        //Soundex::get_options_exact(w_case, dict);
        sndx_opts_cnt += w_case.getSndx_opts()->size();
        sndx_success += std::find(w_case.getSndx_opts()->begin(), w_case.getSndx_opts()->end(), w_case.getCorrect_w())
                         != w_case.getSndx_opts()->end() ? 1 : 0;

        /*
        // Full report - uncomment
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
         */
        foutput << "\t" << w_case.getGed_opts()->size() << "\t";
        foutput << "\t" << w_case.getNgram_opts()->size() << "\t";
        foutput << "\t" << w_case.getSndx_opts()->size() << endl;

        ++total_wrds;
        cout << "Words processed: " << total_wrds << endl;
    }

    foutput << "RUN SUMMARY: " << endl;
    foutput << "Total words: " << total_wrds << "\n\n" << endl;

    foutput << "*** GLOBAL EDIT DISTANCE ***" << endl;
    foutput << "Predictions: " << ged_opts_cnt <<
            "\nSuccess: " << ged_success <<
            "\nPrecision: " << (double)ged_success/ged_opts_cnt <<
            "\nRecall: " << (double)ged_success/total_wrds << endl;
    foutput << "GED parameters:" << endl;
    foutput << "Mat: " << GlobalEdit::getMATCH_C() <<
            " Ins: " << GlobalEdit::getINSERT_C() <<
            " Del: " << GlobalEdit::getDELETE_C() <<
            " Repl: " << GlobalEdit::getREPLACE_C() << endl;
    foutput << "Limit dist: " << GlobalEdit :: getDist_limit() << endl;

    foutput << "\n*** N-GRAM ***" << endl;
    foutput << "Predictions: " << ngram_opts_cnt <<
            "\nSuccess: " << ngram_success <<
            "\nPrecision: " << (double)ngram_success/ngram_opts_cnt <<
            "\nRecall: " << (double)ngram_success/total_wrds << endl;
    foutput << "N-Gram parameters:" << endl;
    foutput << "N: " << NGram::getN() << endl;

    foutput << "\n*** SOUNDEX ***" << endl;
    foutput << "Predictions: " << sndx_opts_cnt <<
            "\nSuccess: " << sndx_success <<
            "\nPrecision: " << (double)sndx_success/sndx_opts_cnt <<
            "\nRecall: " << (double)sndx_success/total_wrds << endl;
    foutput << "Soundex parameters:" << endl;
    foutput << "Truncate to: " << Soundex::getTRUNC_TO() << endl;

    /*
    WordCase w_case = (*cases_db)[0];
    cout << "n-th pair: " << w_case.toString() << endl;
    GlobalEdit::get_options(w_case,gcnst::GConst::ADDR_DICT.c_str());


    for (string tmp : (*(*cases_db)[1].getGed_opts())) {
        cout << tmp << endl;
    }
     */

    /*
    WordCase w_test = WordCase();
    w_test.setMisspell_w("lended");
    string str = "deaden";
    cout << NGram::n_gram_distance_fast(NGram::split_word(w_test.getMisspell_w()), NGram::split_word(str) )  << endl;
     */



    // Close files
    fmisspell.close();
    fcorrect.close();
    fdict.close();
    foutput.close();

    // Free memory
    delete(cases_db);
    delete(dict);
    delete(dict_ngr_sort);

    cout << "Execution time: " << (double)(clock() - timer_start)/CLOCKS_PER_SEC << " s." << endl;

    return 0;
}