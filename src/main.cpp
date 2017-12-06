#include "hmm.h"
#include "util.h"
#include "dictionary.h"
#include "unigram.h"
#include "bigram.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main(void) {
    cout << "Hello, World!" << endl;

    cout << "Reading dictionary.txt" << endl;
    auto dict = Dictionary::Instance();
    for(auto it = dict->_data.begin(); it != dict->_data.end(); it++) {
        cout << (*it).first << tab << ":";
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



    cout << "Reading unigram.txt" << endl;
    auto unigram = Unigram::Instance();
    for(auto it = unigram->_data.begin(); it != unigram->_data.end(); it++) {
        string word;
        Probability prob;
        tie(word, prob) = (*it);
        cout << word << tab << ":" << tab << prob.scale << "e" << prob.exp << endl;
    }
    cout << endl;



    cout << "Reading bigram.txt" << endl;
    auto bigram = Bigram::Instance();
    for(auto it = bigram->_data.begin(); it != bigram->_data.end(); it++) {
        string from;
        string to;
        Probability prob;
        tie(from, to, prob) = (*it);
        cout << from << tab << ">" << tab << to << tab << ":" << tab << prob.scale << "e" << prob.exp << endl;
    }
    cout << endl;
    
    return 0;
}