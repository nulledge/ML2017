#ifndef __probability_h__
#define __probability_h__

#include <string>
using namespace std;

class Probability {
public:
    Probability(void);
    Probability(string str);
    Probability(double scale, long exp);
    ~Probability(void);

public:
    double scale;
    long exp;

public:
    Probability& norm(void);
};

#endif