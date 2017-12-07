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

    unsigned int n_cell = 4;
    Cell cells[n_cell];

    cells[0]._link.push_back(
        make_pair(
            &cells[0],
            Probability(1.0)
        )
    );
    cells[0]._link.push_back(
        make_pair(
            &cells[1],
            Probability(0.5)
        )
    );

    cells[1]._link.push_back(
        make_pair(
            &cells[1],
            Probability(0.8)
        )
    );
    cells[1]._link.push_back(
        make_pair(
            &cells[2],
            Probability(0.5)
        )
    );

    cells[2]._link.push_back(
        make_pair(
            &cells[2],
            Probability(0.8)
        )
    );
    cells[2]._link.push_back(
        make_pair(
            &cells[3],
            Probability(0.5)
        )
    );

/*    for(auto idx = 0U; idx < n_cell; idx++) {
        auto& cell = cells[idx];
        auto& link = cell._link;

        if(idx != n_cell - 1) {
            link.push_back(
                make_pair(
                    &cells[idx + 1],
                    rand_prob()
                )
            );
            link.push_back(
                make_pair(
                    &cells[idx],
                    rand_prob()
                )
            );
        }
    }*/

    for(auto idx = 0U; idx < n_cell; idx ++) {
        auto& cell = cells[idx];
        auto& link = cell._link;

        cout << "idx: " << idx << endl;

        for(auto it = link.begin(); it != link.end(); it ++) {
            Cell* next;
            Probability prob;
            tie(next, prob) = (*it);

            for(auto to = 0U; to < n_cell; to ++) {
                if(&cells[to] != next)
                    continue;
                cout << tab << "(" << to << ", " << prob.str() << ")";
                break;
            }
        } cout << endl;
    } cout << endl;

    cells[0]._log[0] = make_pair(
        nullptr,
        Probability(1.0)
    );
    for(auto step = 1U; step <= 10; step ++) {
        for(auto idx = 0U; idx < n_cell; idx ++) {
            auto& cell = cells[idx];
            auto& link = cell._link;
            auto& record = cell._log;

            if(record.find(step - 1) == record.end())
                continue;

            for(auto it = link.begin(); it != link.end(); it ++) {
                Cell* next;
                Probability prob;
                tie(next, prob) = (*it);

                auto& next_record = next->_log;

                if(next_record.find(step) == next_record.end()) {
                    next_record[step] = make_pair(
                        &cell,
                        record[step - 1].second.mul(prob)
                    );
                }
                else {
                    Probability next_prob = record[step - 1].second.mul(prob);
                    if(next_record[step].second.gt(next_prob))
                        continue;
                    next_record[step] = make_pair(
                        &cell,
                        next_prob
                    );
                }
            }
        }
    }


    cout << cells[0]._log[0].second.str() << endl;

    cout << cells[0]._log[1].second.str() << endl;
    cout << cells[1]._log[1].second.str() << endl;

    cout << "backpropagate" << endl;

    Cell* cell = &cells[n_cell - 1];
    cout << "initialize start point" << endl;
    cout << n_cell - 1;
    for(auto step = 10; step >= 1; step --) {
        auto& record = cell->_log;
        auto prev = record[step].first;

        for(auto idx = 0U; idx < n_cell; idx ++) {
            if(&cells[idx] != prev)
                continue;
            cout << tab << idx;
            break;
        }
        cell = prev;
    } cout << endl;

    return 0;
}