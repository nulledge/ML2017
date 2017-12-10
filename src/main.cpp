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

int Viterbi(const char* path) {
    MFCC mfcc(path);

    auto machine = Machine::Instance();
    auto& cells = machine->_cells;

    cells[machine->_begin]._log[-1] = make_pair(-1, log(1.0));
    for(auto step = 0U; step < mfcc._n_block; step ++) {
        //cout << "step: " << step << endl;
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
                if(isnan(next_prob)){
                    return 1;
                }

                if(cells[next]._log.find(step) == cells[next]._log.end()
                    || cells[next]._log[step].second < next_prob) {
                    cells[next]._log[step] = make_pair(it_cell, next_prob);
                }
            }
        }
    }
    const char* ref = "_8549o17632zz";
    stringstream buffer("");
    
    int marker = machine->_end;
    for(int step = mfcc._n_block - 1; step >= 0; step --) {
        auto prev = cells[marker]._log[step].first;
        
        if(machine->is_word_end(prev) >= 1 and machine->is_word_end(marker) == -1) {
            buffer << ref[machine->is_word_end(prev)];
        }

        marker = prev;
    }

    string str = buffer.str();
    cout << "path: " << path << endl;
    cout << "pred: ";
    for(int idx = (str.size() - 1 > 6 ? 6 : str.size() - 1); idx >= 0; idx --)
        cout << str[idx];
    cout << endl;

    machine->clear();

    return 0;
}

int main(void) {
    Viterbi("dat/tst/m/ah/3o33951.txt");
    Viterbi("dat/tst/f/ap/4241866.txt");

    return 0;
}