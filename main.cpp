#include <iostream>
#include <fstream>
#include <string>

#include "GlobalEdit.h"

using namespace std;

class GlobalEdit;

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

    GlobalEdit temp = GlobalEdit();
    printf("GED = %d\n", temp.global_distance("lended", "deaden"));


    return 0;
}