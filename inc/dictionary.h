#ifndef __dictionary_h__
#define __dictionary_h__

#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;

class Dictionary {
// Singleeton interface.
public:
    static Dictionary* Instance(void) {
        if(_instance == nullptr)
            _instance = new Dictionary();
        return _instance;
    }
private:
    static Dictionary* _instance;

// Constructor and destructor.
private:
    Dictionary(void);
    ~Dictionary(void);

// Method.
private:
    void build(void);

// Member.
public:
    vector<pair<string, vector<string> > > _data;

private:
    static const char * const _path;
    ifstream _file;
};

#endif