#ifndef __unigram_h__
#define __unigram_h__

#include <string>
#include <map>

#define UNIGRAM_KEY     std::string
#define UNIGRAM_VALUE   long double

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

public:
    std::map<UNIGRAM_KEY, UNIGRAM_VALUE> _data;
};

#endif