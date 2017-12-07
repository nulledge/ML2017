#ifndef __cell_h__
#define __cell_h__

#include <vector>
#include <map>
#include <cstdlib>

using namespace std;

class Cell {
public:
    Cell(void);
    ~Cell(void);

public:
    vector<pair<Cell*, long double> > _link;
    map<const unsigned int, pair<Cell*, long double> > _log;
};

#endif