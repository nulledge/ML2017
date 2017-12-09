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

    cout << machine->_cells.size() << endl;
/*
    for(auto it = machine->_word.begin(); it != machine->_word.end(); it++) {
        string      word;
        long double word_begin;

        tie(word, word_begin) = (*it);

        if(strcmp(word.c_str(), "zero"))
            continue;

        cout << word << tab << word_begin << endl;

        for(auto it_link = machine->_cells[machine->_begin]._link.begin();
                it_link != machine->_cells[machine->_begin]._link.end();
                it_link ++) {
            unsigned int to;
            long double prob;
            tie(to, prob) = (*it_link);

            if(to != word_begin)
                continue;
            cout << to << tab << prob << endl;
        }
    }*/

    return 0;
}