#ifndef __dictionary_h__
#define __dictionary_h__

#include <string>
#include <vector>
#include <map>
#include <cstdlib>

#define DICTIONARY_KEY      std::string
#define DICTIONARY_VALUE    std::vector<std::string>
#define DICTIONARY_ENTITY   std::pair<DICTIONARY_KEY, DICTIONARY_VALUE >

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

// Member.
public:
    std::vector< DICTIONARY_ENTITY > _data;
};

#endif