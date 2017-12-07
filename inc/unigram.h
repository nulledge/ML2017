#ifndef __unigram_h__
#define __unigram_h__

#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Unigram {
public:
    static Unigram* Instance(void) {
        if(_instance == nullptr)
            _instance = new Unigram();
        return _instance;
    }
private:
    static Unigram* _instance;

private:
    Unigram(void);
    ~Unigram(void);

private:
    void build(void);

public:
    vector<pair<string, long double> > _data;

private:
    static const char* const _path;
    ifstream _file;
};

#endif