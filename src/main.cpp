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

using namespace std;

int main(void) {
    srand(time(NULL));
    cout << "Hello, World!" << endl;

    auto machine = Machine::Instance();
    auto& cells = machine->_cells;

    {
        auto& link = cells[4]._link;
        for(auto it_link = link.begin(); it_link != link.end(); it_link ++) {
            unsigned int to;
            long double prob;
            tie(to, prob) = *it_link;
            cout << to << tab << prob << endl;
        }
    }

    return 0;
}