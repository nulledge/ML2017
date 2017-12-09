#ifndef __machine_h__
#define __machine_h__

#include "dictionary.h"
#include "unigram.h"
#include "bigram.h"
#include "cell.h"

#include <vector>

using namespace std;

class Node {

};

class Machine{
public:
    static Machine* Instance(void) {
        if(_instance == nullptr)
            _instance = new Machine();
        return _instance;
    }
private:
    static Machine* _instance;

private:
    Machine(void);
    ~Machine(void);

    void build(void);
    void build_words(void);
    void build_unigram(void);
    void build_bigram(void);

public:
    unsigned int                        _begin, _end;
    vector<tuple<string, unsigned int> > _word;
    vector<Cell>                        _cells;
};

#endif