#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

#include "GlobalConst.h"

using namespace std;

/**
 * Launches determination of candidates over a chunk of data set
 * @param cases_db data set
 * @param n number of test case in data set to start with
 * @param dict dictionary (as words)
 * @param dict_ngr_sort dictionary (as sorted arrays of n-grams)
 */
void compute(vector<WordCase> *cases_db, int n, const vector<string> *dict,
             const vector<vector<string>*> *dict_ngr_sort);

/**
 * Launches compute() function in the maximum available number of threads
 * Naive multi-threading implementation:
 * data is splitted evenly between all available threads
 * @param cases_db data set
 * @param n number of test case in data set to start with
 * @param dict dictionary (as words)
 * @param dict_ngr_sort dictionary (as sorted arrays of n-grams)
 */
void calc_multithread(vector<WordCase> *cases_db, int n, const vector<string> *dict,
                      const vector<vector<string>*> *dict_ngr_sort);

string *vect_str(const vector<string> *v) {
    auto res = new string;
    for (const string &s : *v) {
        *res += s;
        *res += " ";
    }
    return res;
}


/**
 * Main function.
 * Gets input parameters
 * Reads data set and dictionary
 * Launches multi-threaded calculation
 * Outputs results into a file
 * @param argc number of app arguments
 * @param argv arg vector. [1]: conf.file, [2]: output file
 * @return 0 if OK, error code otherwise
 */
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

    // Populate dictionary with words and n-gram sets
    ifstream fdict (gcnst::GConst::addr_dict.c_str());
    while (getline(fdict, ln_dict)) {
        dict->push_back(ln_dict);
        dict_ngr_sort->push_back(NGram::split_word(ln_dict));
    }

    // Output text file
    ofstream foutput (argv[2]);
    ofstream fexample ("/Users/stenpety/test/knowtech/comp90049_examples.txt");

    // Here magic comes
    calc_multithread(cases_db, n, dict, dict_ngr_sort);

    // Count all returned candidates and determine success
    for (const WordCase &w_case : *cases_db) {
        unsigned long ged_opts_d = 0, ngr_opts_d = 0;
        int ged_sccs_d = 0, ngr_sccs_d = 0;
        string *v = nullptr;

        ged_opts_d = w_case.getGed_opts()->size();
        ged_opts_cnt += ged_opts_d;

        ged_sccs_d = std::find(w_case.getGed_opts()->begin(), w_case.getGed_opts()->end(), w_case.getCorrect_w())
                       != w_case.getGed_opts()->end() ? 1 : 0;
        ged_success += ged_sccs_d;


        ngr_opts_d = w_case.getNgram_opts()->size();
        ngram_opts_cnt += ngr_opts_d;
        ngr_sccs_d = std::find(w_case.getNgram_opts()->begin(), w_case.getNgram_opts()->end(), w_case.getCorrect_w())
                         != w_case.getNgram_opts()->end() ? 1 : 0;
        ngram_success += ngr_sccs_d;

        if (ged_opts_d >=4 && !ged_sccs_d && ngr_sccs_d) {
            fexample << "GED fail, N-Gram success" << endl;
            v = vect_str(w_case.getGed_opts());
            fexample << "GED\tfail\t" << w_case.toString() << "\t" << *v << endl;
            delete(v);
            v = vect_str(w_case.getNgram_opts());
            fexample << "NGRAM\tsuccess\t" << w_case.toString() << "\t" << *v << endl;
            delete(v);

        }

        if (ged_sccs_d && ngr_opts_d >= 4 && !ngr_sccs_d) {
            fexample << "GED success, N-Gram fail" << endl;
            v = vect_str(w_case.getGed_opts());
            fexample << "GED\tsuccess\t" << w_case.toString() << "\t" << *v << endl;
            delete(v);
            v = vect_str(w_case.getNgram_opts());
            fexample << "NGRAM\tfail\t" << w_case.toString() << "\t" << *v << endl;
            delete(v);

        }

        // Examples search for Soundex - not used
        /*
        opts = w_case.getSndx_opts()->size();
        sndx_opts_cnt += opts;
        sccs = std::find(w_case.getSndx_opts()->begin(), w_case.getSndx_opts()->end(), w_case.getCorrect_w())
                        != w_case.getSndx_opts()->end() ? 1 : 0;
        sndx_success += sccs;

        if (opts >= 10) {
            v = vect_str(w_case.getSndx_opts());
            if (sccs) {
                fexample << "SNDX\t10+\t" << w_case.toString() << "\t" << *v << endl;
            } else {
                fexample << "SNDX\t10-\t" << w_case.toString() << "\t" << *v << endl;
            }
            delete(v);
        } else {
            if (opts == 1 && sccs) {
                v = vect_str(w_case.getSndx_opts());
                fexample << "SNDX\t!!!\t" << w_case.toString() << "\t" << *v << endl;
                delete(v);
            }
        }
         */

        ++total_wrds;

    }

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
    foutput << "Score limit: " << NGram::getScore_lim() << endl;
    foutput << "Dice threshold: " << NGram::getDice_th() << endl;

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
    fexample.close();

    // Free memory
    delete(cases_db);
    delete(dict);
    delete(dict_ngr_sort);

    // Works incorrectly in multi-thread environment :(
    cout << "Execution time: " << (double)(clock() - timer_start)/CLOCKS_PER_SEC << " s." << endl;

    return 0;
}

void compute(vector<WordCase> *cases_db, int n, const vector<string> *dict,
             const vector<vector<string> *> *dict_ngr_sort) {
    int i;
    mutex mutex;

    /*
    mutex.lock();
    *n += CHUNK;
    mutex.unlock();
     */

    // How many cases should each thread take
    unsigned long chunk = cases_db->size() / thread::hardware_concurrency() + 1;

    unsigned long last = n+chunk >= cases_db->size() ? cases_db->size() : n+chunk;

    for (i = n; i < last; ++i) {

        cout << "Processing word: " << i << endl;
        //GlobalEdit::get_options((*cases_db)[i], dict);
        NGram::get_options((*cases_db)[i], dict_ngr_sort, dict);
        //Soundex::get_options_exact((*cases_db)[i], dict);
    }
}

void calc_multithread(vector<WordCase> *cases_db, int n, const vector<string> *dict,
                      const vector<vector<string>*> *dict_ngr_sort) {
    vector<thread> threads;

    // How many threads are available
    unsigned max_threads = thread::hardware_concurrency();
    unsigned long chunk = (cases_db->size() / max_threads + 1);
    cout << "Max threads: " << max_threads << ". Chunk size: " << chunk << endl;

    unsigned long i;

    // Run threads!
    for (i = 0; i < max_threads; ++i) {
        threads.emplace_back(compute, cases_db, (n+i)*chunk, dict, dict_ngr_sort);
        cout << "Thread " << i << " pushed, n = " << (n+i)*chunk << endl;
    }

    // Join all threads
    for(i = 0; i < threads.size() ; i++) {
        threads.at(i).join();
    }
}