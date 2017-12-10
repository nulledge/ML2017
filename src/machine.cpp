#include "machine.h"
#include "util.h"
#include "hmm.h"

#include <iostream>

using namespace std;

Machine* Machine::_instance = nullptr;

Machine::Machine(void)
{
    build();
}
Machine::~Machine(void) {

}


int Machine::is_word_end(const unsigned int cell) const {
    for(auto it_word = 0; it_word != _word.size(); it_word ++) {
        if(get<2>(_word[it_word]) == cell)
            return it_word;
    }
    return -1;
}

void Machine::clear(void) {
    for(auto it_cell = _cells.begin(); it_cell != _cells.end(); it_cell ++) {
        auto& cell = *it_cell;
        cell._log.clear();
    }
}

void Machine::build(void) {
    build_words();
    build_unigram();
    build_bigram();
}

void Machine::build_bigram(void) {
    auto& bi = Bigram::Instance()->_data;

    for(auto it_bi = bi.begin(); it_bi != bi.end(); it_bi ++) {
        string from, to;
        long double prob;

        tie(from, to) = (*it_bi).first;
        prob = (*it_bi).second;

        for(auto from_it = _word.begin(); from_it != _word.end(); from_it ++) {
            if(strcmp(from.c_str(), get<0>(*from_it).c_str()))
                continue;
            
            for(auto to_it = _word.begin(); to_it != _word.end(); to_it ++) {
                if(strcmp(to.c_str(), get<0>(*to_it).c_str()))
                    continue;
                
                _cells[get<2>(*from_it)]._link.push_back(make_pair(get<1>(*to_it), prob));
                //cout << from << get<2>(*from_it) << tab << to << get<1>(*to_it) << tab << prob <<endl;
            }
        }
    }
}

void Machine::build_unigram(void) {
    auto& uni = Unigram::Instance()->_data;

    for(auto it_word = _word.begin(); it_word != _word.end(); it_word ++) {
        string word;
        unsigned int word_begin, word_end;
        tie(word, word_begin, word_end) = *it_word;

        //cout << word << tab << word_begin << tab << word_end << endl;

        auto& link = _cells[_begin]._link;
        for(auto it_link = link.begin(); it_link != link.end(); it_link ++) {
            const unsigned int& to = (*it_link).first;
            if(to != word_begin)
                continue;
            (*it_link).second = uni[word];
        }
    }
}

void Machine::build_words(void) {

    _cells.push_back(Cell());
    _cells.push_back(Cell());

    _begin  = 0;
    _end    = 1;

    auto& dict = Dictionary::Instance()->_data;
    for(auto it_dict = dict.begin(); it_dict != dict.end(); it_dict ++) {
        const DICTIONARY_KEY&   word            = (*it_dict).first;
        const DICTIONARY_VALUE& phones          = (*it_dict).second;
        unsigned int            n_cells_in_word = 0U;

        // Find how many cells in the word.
        for(auto it_phoneme = phones.begin(); it_phoneme != phones.end(); it_phoneme ++) {
            const string&       phoneme             = (*it_phoneme);
            const bool          is_sp               = strcmp(phoneme.c_str(), "sp") == 0;
            const unsigned int  n_cells_in_phoneme  = is_sp ? 1 : 3;

            n_cells_in_word += n_cells_in_phoneme;
        }

        // Add cells in need.
        for(auto idx = 0U; idx < n_cells_in_word; idx ++)
            _cells.push_back(Cell());

        const unsigned int  cell_begin      = _cells.size() - n_cells_in_word;
        const unsigned int  cell_end        = _cells.size();
        unsigned int        n_cells_done    = 0;
        unsigned int        prev_cell       = _begin;

        _word.push_back(make_tuple(word, cell_begin, cell_end - 1));
        
        /*cout << "word: " << word << endl;
        cout << tab << "N_CELLS_IN_WORD: " << n_cells_in_word << endl;
        cout << tab << "Phones:";*/

        for(auto it_phoneme = phones.begin(); it_phoneme != phones.end(); it_phoneme ++) {
            const string&       phoneme             = (*it_phoneme);
            const bool          is_sp               = strcmp(phoneme.c_str(), "sp") == 0;
            const unsigned int  n_cells_in_phoneme  = is_sp ? 1 : 3;
            hmmType*            pretrained          = nullptr;

            for(auto idx = 0U; idx < N_PHONES; idx ++) {
                if(strcmp(pretrained_phones[idx].name, phoneme.c_str()) == 0) {
                    pretrained = &pretrained_phones[idx];
                    break;
                }
            }
            //cout << " " << pretrained->name;

            unsigned int    cells_in_phoneme[N_STATE + 2];

            cells_in_phoneme[0] = prev_cell;
            for(auto idx = 0; idx < n_cells_in_phoneme; idx ++) {
                cells_in_phoneme[idx + 1] = cell_begin + n_cells_done + idx;
                _cells[cells_in_phoneme[idx + 1]]._out = &pretrained->state[idx];
            }
            cells_in_phoneme[n_cells_in_phoneme + 1] =
                cell_begin + n_cells_done + n_cells_in_phoneme == cell_end ?
                _end
                : cell_begin + n_cells_done + n_cells_in_phoneme;

            for(auto from = 0U; from < N_STATE + 2; from ++) {
                for(auto to = 0U; to < N_STATE + 2; to ++) {
                    if(pretrained->tp[from][to] == 0.0f)
                        continue;

                    _cells[cells_in_phoneme[from]]._link.push_back(
                        make_pair(
                            cells_in_phoneme[to],
                            pretrained->tp[from][to]
                        )
                    );
                }
            }
            prev_cell = cells_in_phoneme[n_cells_in_phoneme + 1];
            n_cells_done += n_cells_in_phoneme;

        } //cout << endl;
    } //cout << endl;
}