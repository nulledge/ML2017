#include "dictionary.h"

#include <sstream>

Dictionary* Dictionary::_instance = nullptr;
const char * const Dictionary::_path = "dat/dictionary.txt";

Dictionary::Dictionary(void) {
    _file.open(_path);
    build();
}
Dictionary::~Dictionary(void) {
    _file.close();
}

void Dictionary::build(void) {
    string line;
    string word, phoneme;

    while(getline(_file, line)) {
        stringstream stream(line);

        stream >> word;
        vector<string> vec_phones;
        while(stream >> phoneme) {
            vec_phones.push_back(phoneme);
        }
        _data.push_back(make_pair(word, vec_phones));
    }
}