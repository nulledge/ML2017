#include "hmm.h"
#include "util.h"
#include "dictionary.h"
#include "unigram.h"
#include "bigram.h"
#include "mfcc.h"
#include "cell.h"
#include "probability.h"

#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(void) {
    srand(time(NULL));
    cout << "Hello, World!" << endl;

    auto rand_prob = []() {
        return Probability(
            (double)(rand() % 99) / 100.0
        ).norm();
    };

    cout << norm_dist(Probability(0.0), 0.0, 1.0).str() << endl;

    return 0;
}