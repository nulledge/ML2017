#include "dictionary.h"

#include <fstream>
#include <sstream>

Dictionary* Dictionary::_instance = nullptr;

Dictionary::Dictionary(void) {
    const auto      path = "dat/dictionary.txt";
    std::ifstream   file(path);

    std::string line;
    while(getline(file, line)) {
        std::stringstream   stream(line);
        std::string         word;
        DICTIONARY_KEY      key;
        DICTIONARY_VALUE    value;

        stream >> key;
        while(stream >> word) {
            value.push_back(word);
        }

        DICTIONARY_ENTITY   entity(make_pair(key, value));
        _data.push_back(entity);
    }

    file.close();
}
Dictionary::~Dictionary(void) {
}