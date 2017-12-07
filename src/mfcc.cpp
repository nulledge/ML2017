#include "mfcc.h"
#include "util.h"

#include <string>
#include <sstream>
#include <fstream>

using namespace std;

MFCC::MFCC(void)
    : _n_block(0), _n_dimension(0), _data(nullptr)
{
}

MFCC::MFCC(const char* path) {
    ifstream file(path);
    string line;
    long double prob;

    {
        getline(file, line);
        stringstream stream(line);
        stream >> _n_block >> _n_dimension;
    }

    _data = (long double**)malloc(sizeof(long double*) * _n_block * _n_dimension);
    for(auto idx = 0U; idx < _n_block; idx += 1) {
        _data[idx] = (long double*)malloc(sizeof(long double) * _n_dimension);
    }

    unsigned int idx_line = 0, idx_dimension = 0;
    while(getline(file, line)) {
        stringstream stream(line);
        idx_dimension = 0;

        while(stream >> prob) {
            _data[idx_line][idx_dimension] = prob;
            idx_dimension += 1;
        }

        idx_line += 1;
    }
}

MFCC::~MFCC(void) {
    SAFE_DELETE(_data);
}