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

    const auto path = "dat/tst/f/ak/44z5938.txt";
    MFCC mfcc(path);

    cells[machine->_begin]._log[-1] = make_pair(-1, log(1.0));
    for(auto step = 0U; step < mfcc._n_block; step ++) {
        cout << "step: " << step << endl;
        //for(auto it_cell = cells.begin(); it_cell != cells.end(); it_cell ++) {
        for(auto it_cell = 0U; it_cell < cells.size(); it_cell ++) {
            auto& cell = cells[it_cell];

            if(cell._log.find(step - 1) == cell._log.end())
                continue;

            auto prev_prob = cell._log[step - 1].second;

            for(auto it_link = cell._link.begin(); it_link != cell._link.end(); it_link ++) {
                auto link = *it_link;
                auto next = link.first;
                auto trans = link.second;

                long double next_prob = prev_prob + log(trans) + (next == machine->_end ? 0 : cells[next].observe(&mfcc, step));
                if(isnan(next_prob) ){
                    cout << "step: " << step << endl;
                    cout << "from: " << it_cell << tab << "to: " << next << endl;
                    cout << "prob: " << prev_prob << tab << next_prob << endl;
                    cout << "log(trans): " << log(trans) << endl;
                    cout << "observe: " << cells[next].observe(&mfcc, step) << endl;
                    return 1;
                }

                if(cells[next]._log.find(step) == cells[next]._log.end()) {
                    cells[next]._log[step] = make_pair(it_cell, next_prob);
                }
                else if(cells[next]._log[step].second < next_prob) {
                    cells[next]._log[step] = make_pair(it_cell, next_prob);
                }
            }
        }
    }

    cout << cells[machine->_end]._log[mfcc._n_block - 1].first << endl;
    cout << cells[machine->_end]._log[mfcc._n_block - 1].second << endl;

/*    auto machine = Machine::Instance();
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
        auto n_cells = cells.size();

        for(auto step = 0U; step < mfcc->_n_block; step ++) {
            for(auto it_cell = cells.begin(); it_cell != cells.end(); it_cell ++) {
                Cell& cell
            }
        }
    }*/

    return 0;
}