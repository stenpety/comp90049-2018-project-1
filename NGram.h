//
// Created by Petr Stenin on 30/03/2018.
//

#ifndef COMP90049_2018_PROJECT_1_NGRAM_H
#define COMP90049_2018_PROJECT_1_NGRAM_H

#include <string>
#include <vector>
#include <limits>

#include "WordCase.h"

#define DICE_RNG 0.1

class WordCase;

class NGram {
private:
    static int N;
    static int score_lim;
    static double dice_th;

    // Legacy code
    static int n_gram_distance(const std::string &, const std::string &);

    /**
     * Calculates N-Gram score for given sets of n-grams (representing words)
     * @return score
     */
    static int n_gram_distance_fast(const std::vector<std::string> *, const std::vector<std::string> *);

    /**
     * Calculates Dice coefficient for the 2 sets of n-grams (representing words)
     * @return Dice coefficient
     */
    static double n_gram_dice(const std::vector<std::string> *, const std::vector<std::string> *);
public:
    NGram();

    /**
     * Gets all candidates for a given word from the dictionary
     * Does not return anything
     * Modifies input parameter of WordCase type
     */
    static void get_options(WordCase &, const std::vector<std::vector<std::string>*> *,
            const std::vector<std::string> *);

    static void setNgramParms(int, int, double);

    static int getN();

    static int getScore_lim();

    static double getDice_th();

    static std::vector<std::string> *split_word(const std::string &);
};


#endif //COMP90049_2018_PROJECT_1_NGRAM_H
