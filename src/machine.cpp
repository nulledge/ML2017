#include "machine.h"
#include "util.h"
#include "hmm.h"

#include <iostream>

using namespace std;

Machine* Machine::_instance = nullptr;

Machine::Machine(void)
    :   _dict(Dictionary::Instance()),
        _uni(Unigram::Instance()),
        _bi(Bigram::Instance())
{
    build();
}
Machine::~Machine(void) {

}

void Machine::build(void) {
    _cells.push_back(Cell());
    _cells.push_back(Cell());
    
    _begin = &_cells[0];
    _end = &_cells[1];

    _begin->_link.push_back(make_pair(nullptr, 0.0));

    for(auto it_word = _dict->_data.begin(); it_word != _dict->_data.end(); it_word ++) {
        string& word = (*it_word).first;
        vector<string>& word_phones = (*it_word).second;

        auto n_cells_in_word = 0U;

        // Find how many cells in the word.
        for(auto it_phoneme = word_phones.begin(); it_phoneme != word_phones.end(); it_phoneme ++) {
            string& phoneme = (*it_phoneme);
            bool is_sp = strcmp(phoneme.c_str(), "sp") == 0;
            unsigned int n_cells_in_phoneme = is_sp ? 1 : 3;
            n_cells_in_word += n_cells_in_phoneme;
        }

        cout << "N_CELLS_IN_WORD: " << n_cells_in_word << endl;

        // Add cells in need.
        for(auto idx = 0U; idx < n_cells_in_word; idx ++)
            _cells.push_back(Cell());

        cout << tab << _cells.size() << endl;
        
        unsigned int n_cells_done = 0U;
        Cell* begin = _begin;
        // Connect the links.
        cout << tab << word;
        for(auto it_phoneme = word_phones.begin(); it_phoneme != word_phones.end(); it_phoneme ++) {
            string& phoneme = (*it_phoneme);
            bool is_sp = strcmp(phoneme.c_str(), "sp") == 0;
            unsigned int n_cells_in_phoneme = is_sp ? 1 : 3;
            hmmType* pretrained;

            for(auto idx = 0U; idx < N_PHONES; idx ++) {
                if(strcmp(phones[idx].name, phoneme.c_str()))
                    continue;
                pretrained = &phones[idx];
                break;
            }

            cout << tab << pretrained->name;

            Cell* cells_in_phoneme[N_STATE + 2];
            cells_in_phoneme[0] = begin;

            for(auto idx = 0; idx < n_cells_in_phoneme; idx ++)
                cells_in_phoneme[idx + 1] = &_cells[_cells.size() - n_cells_in_word + n_cells_done + idx];
            if(n_cells_done + n_cells_in_phoneme == n_cells_in_word)
                cells_in_phoneme[n_cells_in_phoneme + 1] = _end;
            else
                cells_in_phoneme[n_cells_in_phoneme + 1] = &_cells[_cells.size() - n_cells_in_word + n_cells_done + n_cells_in_phoneme];

            cout << endl;

            for(auto from = 0U; from < N_STATE + 2; from ++) {
                for(auto to = from; to < N_STATE + 2; to ++) {
                    if(pretrained->tp[from][to] == 0.0f)
                        continue;

                    cout << tab << tab;
                    if(cells_in_phoneme[from] == _begin) cout << "B";
                    for(auto idx = 0; idx < n_cells_in_phoneme; idx ++)
                        if(cells_in_phoneme[from] == &_cells[_cells.size() - n_cells_in_word + n_cells_done + idx]) {
                            cout << idx + 1;
                            break;
                        }
                    cout <<  "/";
                    if(cells_in_phoneme[to] == _end) cout << "E";
                    for(auto idx = 0; idx < n_cells_in_phoneme; idx ++)
                        if(cells_in_phoneme[to] == &_cells[_cells.size() - n_cells_in_word + n_cells_done + idx]) {
                            cout << idx + 1;
                            break;
                        }
                    cout << endl;

                    cells_in_phoneme[from]->_link.push_back(
                        make_pair(
                            cells_in_phoneme[to],
                            pretrained->tp[from][to]
                        )
                    );
                }
            }
            begin = cells_in_phoneme[n_cells_in_phoneme + 1];
            n_cells_done += n_cells_in_phoneme;
        } cout << endl;
    } cout << endl;
}