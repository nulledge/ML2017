#ifndef __bigram_h__
#define __bigram_h__

#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Bigram {
public:
    static Bigram* Instance(void) {
        if(_instance == nullptr)
            _instance = new Bigram();
        return _instance;
    }
private:
    static Bigram* _instance;

private:
    Bigram(void);
    ~Bigram(void);

private:
    void build(void);

public:
    vector<tuple<string, string, long double> > _data;

private:
    static const char* const _path;
    ifstream _file;
};

#endif