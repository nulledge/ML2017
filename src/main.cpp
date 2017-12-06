#include "hmm.h"
#include "util.h"
#include "dictionary.h"
#include "unigram.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main(void) {
    cout << "Hello, World!" << endl;

    auto dict = Dictionary::Instance();
    for(auto it = dict->_data.begin(); it != dict->_data.end(); it++) {
        cout << (*it).first << ": ";
        for(auto it_inner = (*it).second.begin(); it_inner != (*it).second.end(); it_inner ++) {
            cout << tab << (*it_inner);
            
            for(unsigned int idx = 0; idx < N_PHONES; idx ++) {
                if(strcmp(phones[idx].name, (*it_inner).c_str()) == false) {
                    cout << "*";
                    break;
                }
            }
        }
        cout << endl;
    }

    cout << endl;

    auto unigram = Unigram::Instance();
    for(auto it = unigram->_data.begin(); it != unigram->_data.end(); it++) {
        cout << (*it).first << ": " << tab << (*it).second.scale << "e" << (*it).second.exp << endl;
    }
    
    return 0;
}