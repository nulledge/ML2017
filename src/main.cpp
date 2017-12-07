#include "hmm.h"
#include "util.h"
#include "dictionary.h"
#include "unigram.h"
#include "bigram.h"
#include "mfcc.h"
#include "cell.h"

#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(void) {
    srand(time(NULL));
    cout << "Hello, World!" << endl;

    long double prob = 0.0;
    long double pivot = -5.0;
    long double base = 2.867e-7;
    long double sum = 0;
    long double delta = 1e-4;

    while(pivot < prob) {
        sum += norm_dist(pivot, 0, 1);
        pivot += delta;
    }
    cout << base + sum * delta << endl;

    cout << norm_dist(0, 0, 1) << endl;

    return 0;
}