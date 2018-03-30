#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv) {

    string addr_misspell = "/Users/stenpety/test/knowtech/misspell.txt";
    string addr_fcorrect = "/Users/stenpety/test/knowtech/correct.txt";
    string addr_fdict = "/Users/stenpety/test/knowtech/dictionary.txt";
    string line;

    ifstream fmisspell (addr_misspell.c_str());

    while (getline(fmisspell, line)) {
        cout << line << endl;
    }



    return 0;
}