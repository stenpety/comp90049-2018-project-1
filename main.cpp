#include <iostream>
#include <fstream>
#include <string>

#include "GlobalEdit.h"
#include "NGram.h"
#include "Soundex.h"

using namespace std;

int main(int argc, char **argv) {

    string addr_misspell = "/Users/stenpety/test/knowtech/misspell.txt";
    string addr_fcorrect = "/Users/stenpety/test/knowtech/correct.txt";
    string addr_fdict = "/Users/stenpety/test/knowtech/dictionary.txt";
    string line;

    /*
    ifstream fmisspell (addr_misspell.c_str());

    while (getline(fmisspell, line)) {
        cout << line << endl;
    }
     */

    //GlobalEdit ge_temp = GlobalEdit();
    //printf("GED = %d\n", ge_temp.edit_distance("lended", "deaden", false));

    /*
    NGram ng3_temp = NGram(3);
    printf("3-Gram : %d\n", ng3_temp.n_gram_distance("lended","deaden"));


    NGram ng2_temp = NGram(2);
    printf("2-Gram : %d\n", ng2_temp.n_gram_distance("lended","lent"));
     */

    /*
    Soundex sndx_temp = Soundex();
    string *snd_str = sndx_temp.sndx_convert("lemonadelemonadelemonade");
    cout << *snd_str << endl;

    delete(snd_str);
     */

    return 0;
}