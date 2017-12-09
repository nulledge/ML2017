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
    void build_word(void);
    pair<Cell*, Cell*> build_phoneme(const string& phoneme);

private:
    Cell*           _begin;
    Cell*           _end;
    vector<Cell>    _cells;
    Dictionary*     _dict;
    Unigram*        _uni;
    Bigram*         _bi;
};

#endif