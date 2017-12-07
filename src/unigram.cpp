#include "unigram.h"

#include <sstream>

Unigram* Unigram::_instance = nullptr;
const char * const Unigram::_path = "dat/unigram.txt";

Unigram::Unigram(void) {
    _file.open(_path);
    build();
}
Unigram::~Unigram(void) {

}


void Unigram::build(void) {
    string line;
    string word;
    long double prob;

    while(getline(_file, line)) {
        stringstream stream(line);

        stream >> word >> prob;

        _data.push_back(make_pair(word, prob));
    }
}