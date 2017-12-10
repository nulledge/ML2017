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
#include <dirent.h>

using namespace std;

int Viterbi(const char* path, ostream& out) {
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
    /*const char* ref = "_8549o17632zz";
    stringstream buffer("");*/
    vector<string> buffer;
    
    int marker = machine->_end;
    for(int step = mfcc._n_block - 1; step >= 0; step --) {
        auto prev = cells[marker]._log[step].first;
        
        if(machine->is_word_end(prev) >= 1 and machine->is_word_end(marker) == -1) {
            buffer.push_back(get<0>(machine->_word[machine->is_word_end(prev)]));
        }

        marker = prev;
    }

    
    for(int idx = (buffer.size() - 1 > 6 ? 6 : buffer.size() - 1); idx >= 0; idx --)
        out << buffer[idx] << endl;
    out << "." << endl;

    machine->clear();

    return 0;
}

int main(void) {

    ofstream rec("recognized.txt");
    
    rec << "#!MLF!#" << endl;

    dirent* dir         = nullptr;

    string  tst_path    = "dat/tst/";
    auto*   tst_dir     = opendir(tst_path.c_str());

    while((dir = readdir(tst_dir)) != NULL) {
        if(strcmp(dir->d_name, ".") == 0
            || strcmp(dir->d_name, "..") == 0)
            continue;

        string  gen_path    = tst_path + string(dir->d_name) + string("/");
        auto*   gen_dir     = opendir(gen_path.c_str());

        while((dir = readdir(gen_dir)) != NULL) {
            if(strcmp(dir->d_name, ".") == 0
                || strcmp(dir->d_name, "..") == 0)
                continue;

            string  par_path    = gen_path + string(dir->d_name) + string("/");
            auto*   par_dir     = opendir(par_path.c_str());

            while((dir = readdir(par_dir)) != NULL) {
                if(strcmp(dir->d_name, ".") == 0
                    || strcmp(dir->d_name, "..") == 0)
                    continue;

                string  mfcc_path   = par_path + string(dir->d_name);
                //cout << mfcc_path << endl;
                rec << "\"" << mfcc_path.substr(4, 17) << "rec" <<  "\"" << endl;
                Viterbi(mfcc_path.c_str(), rec);
            }

            closedir(par_dir);
        }
        
        closedir(gen_dir);
    }

    closedir(tst_dir);

    rec.close();

    return 0;
}