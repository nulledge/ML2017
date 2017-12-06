#ifndef __probability_h__
#define __probability_h__

class Probability {
public:
    Probability(void);
    Probability(double scale, long exp);
    ~Probability(void);

public:
    double scale;
    long exp;
};

#endif