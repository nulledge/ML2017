#ifndef __cell_h__
#define __cell_h__

#include "probability.h"

#include <vector>
#include <map>
#include <cstdlib>

using namespace std;

class Cell {
public:
    Cell(void);
    ~Cell(void);

public:
    vector<pair<Cell*, Probability> > _link;
    map<const unsigned int, pair<Cell*, Probability> > _log;
};

#endif