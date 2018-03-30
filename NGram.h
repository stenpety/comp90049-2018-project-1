//
// Created by Petr Stenin on 30/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_NGRAM_H
#define COMP90049_2018_PROJECT_1_NGRAM_H

#include <string>
#include <vector>

class NGram {
private:
    int n;
public:
    explicit NGram(int n);
    int n_gram_distance(std::string, std::string);

};


#endif //COMP90049_2018_PROJECT_1_NGRAM_H
