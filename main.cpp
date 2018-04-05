#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <thread>
#include <mutex>

#include "GlobalConst.h"
#include "WordCase.h"

#define CHUNK 5

using namespace std;

class SpellingCorr {
    std::mutex mutex;
public:
    int total_wrds = 0;
    int ged_opts_cnt = 0, ged_success = 0;
    int ngram_opts_cnt = 0, ngram_success = 0;
    int sndx_opts_cnt = 0, sndx_success = 0;

    void compute(vector<WordCase> *cases_db, int *n, vector<string> *dict, vector<vector<string>*> *dict_ngr_sort) {
        int i;

        mutex.lock();
        *n += CHUNK;
        mutex.unlock();

        for (i = *n-CHUNK; i < *n; ++i) {
            WordCase w_case = (*cases_db)[i];

            GlobalEdit::get_options(w_case, dict);
            NGram::get_options(w_case, dict_ngr_sort, dict);
            Soundex::get_options_exact(w_case, dict);

            mutex.lock();
            ged_opts_cnt += w_case.getGed_opts()->size();
            ged_success += std::find(w_case.getGed_opts()->begin(), w_case.getGed_opts()->end(), w_case.getCorrect_w())
                           != w_case.getGed_opts()->end() ? 1 : 0;

            ngram_opts_cnt += w_case.getNgram_opts()->size();
            ngram_success += std::find(w_case.getNgram_opts()->begin(), w_case.getNgram_opts()->end(), w_case.getCorrect_w())
                             != w_case.getNgram_opts()->end() ? 1 : 0;

            sndx_opts_cnt += w_case.getSndx_opts()->size();
            sndx_success += std::find(w_case.getSndx_opts()->begin(), w_case.getSndx_opts()->end(), w_case.getCorrect_w())
                            != w_case.getSndx_opts()->end() ? 1 : 0;

            ++total_wrds;
            mutex.unlock();
        }
    }
};

SpellingCorr *calc_multithread(vector<WordCase> *cases_db, int *n, vector<string> *dict, vector<vector<string>*> *dict_ngr_sort) {
    auto spelling_corr = new SpellingCorr();
    vector<thread> threads;
    int i;
    for (i = 0; i < 8; ++i) {
        threads.push_back(thread(&SpellingCorr::compute, &spelling_corr, cases_db, n, dict, dict_ngr_sort));
    }

    for(int i = 0; i < threads.size() ; i++) {
        threads.at(i).join();
    }
    return spelling_corr;
}

int main(int argc, char **argv) {

    string ln_misspell, ln_correct, ln_dict;
    int n = 0;
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

    // Get config file
    gcnst::GConst::config(argv[1]);

    // Open files with misspelled and correct words
    ifstream fmisspell (gcnst::GConst::addr_msspl.c_str());
    ifstream fcorrect (gcnst::GConst::addr_crct.c_str());

    // Populate db of WordCase's
    WordCase temp = WordCase();
    while (getline(fmisspell, ln_misspell)) {
        getline(fcorrect, ln_correct);
        temp.setMisspell_w(ln_misspell);
        temp.setCorrect_w(ln_correct);
        cases_db->push_back(temp);
    }

    // Populate dictionary
    ifstream fdict (gcnst::GConst::addr_dict.c_str());
    while (getline(fdict, ln_dict)) {
        dict->push_back(ln_dict);
        dict_ngr_sort->push_back(NGram::split_word(ln_dict));
    }

    // Output text file
    ofstream foutput (argv[2]);

    // Here magic comes

    SpellingCorr *spelling_corr = calc_multithread(cases_db, &n, dict, dict_ngr_sort);
    total_wrds = spelling_corr->total_wrds;
    ged_opts_cnt = spelling_corr->ged_opts_cnt;
    ged_success = spelling_corr->ged_success;
    ngram_opts_cnt = spelling_corr->ngram_opts_cnt;
    ngram_success = spelling_corr->ngram_success;
    sndx_opts_cnt = spelling_corr->sndx_opts_cnt;
    sndx_success = spelling_corr->sndx_success;


    // Form import
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

    // Close files
    fmisspell.close();
    fcorrect.close();
    fdict.close();
    foutput.close();

    // Free memory
    delete(cases_db);
    delete(dict);
    delete(dict_ngr_sort);
    delete(spelling_corr);

    cout << "Execution time: " << (double)(clock() - timer_start)/CLOCKS_PER_SEC << " s." << endl;

    return 0;
}