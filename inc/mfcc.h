#ifndef __mfcc_h__
#define __mfcc_h__

class MFCC {
public:
    MFCC(void);
    MFCC(const char * path);
    ~MFCC(void);

public:
    unsigned int _n_dimension;
    unsigned int _n_block;
    long double** _data;
};

#endif