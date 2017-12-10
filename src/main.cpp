#include "hmm.h"
#include "util.h"
#include "dictionary.h"
#include "unigram.h"
#include "bigram.h"
#include "mfcc.h"
#include "cell.h"
#include "machine.h"

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

int main(void) {
    srand(time(NULL));
    cout << "Hello, World!" << endl;

    auto machine = Machine::Instance();
    auto& cells = machine->_cells;

    {
        auto& link = cells[2]._link;
        for(auto it_link = link.begin(); it_link != link.end(); it_link ++) {
            unsigned int to;
            long double prob;
            tie(to, prob) = *it_link;
            cout << to << tab << prob << endl;
        }
    }

    {
        const char* const path = "dat/tst/f/ak/44z5938.txt";
        MFCC mfcc(path);
        for(auto step = 0U; step < 30; step ++ )
            cout << cells[2].observe(&mfcc, step) << endl;
    }

    return 0;
}