#include "bigram.h"

#include <sstream>

Bigram* Bigram::_instance = nullptr;
const char * const Bigram::_path = "dat/bigram.txt";

Bigram::Bigram(void) {
    _file.open(_path);
    build();
}
Bigram::~Bigram(void) {

}


void Bigram::build(void) {
    string line;
    string from, to;
    double probability;

    while(getline(_file, line)) {
        stringstream stream(line);

        stream >> from >> to >> probability;

        _data.push_back(make_tuple(from, to, Probability(probability, 0).norm()));
    }
}