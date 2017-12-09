#include "bigram.h"

#include <sstream>
#include <fstream>

Bigram* Bigram::_instance = nullptr;

Bigram::Bigram(void) {
    const auto      path = "dat/bigram.txt";
    std::ifstream   file(path);
    
    std::string line;
    std::string from, to;
    long double prob;

    while(getline(file, line)) {
        std::stringstream stream(line);
        stream >> from >> to >> prob;

        BIGRAM_KEY      key(from, to);
        BIGRAM_VALUE    value(prob);
        
        _data[key] = value;
    }
}
Bigram::~Bigram(void) {

}