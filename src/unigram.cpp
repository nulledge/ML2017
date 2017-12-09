#include "unigram.h"

#include <fstream>
#include <sstream>

Unigram* Unigram::_instance = nullptr;

Unigram::Unigram(void) {
    const auto      path = "dat/unigram.txt";;
    std::ifstream   file(path);

    std::string     line, word;
    long double     prob;

    while(getline(file, line)) {
        std::stringstream stream(line);
        stream >> word >> prob;

        UNIGRAM_KEY     key(word);
        UNIGRAM_VALUE   value(prob);
        _data[key] = value;
    }
    file.close();
}
Unigram::~Unigram(void) {

}