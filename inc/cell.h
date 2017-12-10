#ifndef __cell_h__
#define __cell_h__

#include "hmm.h"
#include "mfcc.h"

#include <vector>
#include <map>
#include <cstdlib>

using namespace std;

class Cell {
public:
    Cell(void);
    ~Cell(void);

    long double observe(const MFCC* mfcc, const unsigned int step);

public:
    stateType*                                          _out;
    vector<pair<unsigned int, long double> >            _link;
    map<unsigned int, pair<unsigned int, long double> > _log;
};

#endif