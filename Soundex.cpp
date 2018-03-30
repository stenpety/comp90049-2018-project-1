//
// Created by Petr Stenin on 30/03/2018.
//

#include "Soundex.h"

std::string *Soundex::sndx_convert(std::string cnd) {
    auto res = new std::string;
    int i;

    res->append(cnd.substr(0,1));


    for (i = 1; i < cnd.length(); ++i) {
        switch (cnd[i]) {
            case 'a': case 'e': case 'h': case 'i': case 'o': case 'u': case 'w': case 'y':
                res->append("0");
                break;
            case 'b': case 'p': case 'f': case 'v':
                res->append("1");
                break;
            case 'c': case 'g': case 'j': case 'k': case 'q': case 's': case 'x': case 'z':
                res->append("2");
                break;
            case 'd': case 't':
                res->append("3");
                break;
            case 'l':
                res->append("4");
                break;
            case 'm': case 'n':
                res->append("5");
                break;
            case 'r':
                res->append("6");
                break;
            default:
                break;
        }
    }

    for (i = 0; i < res->length(); ++i) {
        if ((*res)[i] == '0') {
            res->erase((unsigned long)i, 1);
        }
    }
    i = 0;
    while (i < res->length()-1) {
        if ((*res)[i] == (*res)[i+1]) {
            res->erase((unsigned long)i+1,1);
        } else {
            ++i;
        }
    }

    if (res->length() > 4) {
        *res = res->substr(0,4);
    }

    return res;
}
