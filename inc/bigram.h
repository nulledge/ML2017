#ifndef __bigram_h__
#define __bigram_h__

#include <cstdlib>
#include <string>
#include <map>

#define BIGRAM_KEY      std::pair<std::string, std::string>
#define BIGRAM_VALUE    long double

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

public:
    std::map<BIGRAM_KEY, BIGRAM_VALUE> _data;
};

#endif