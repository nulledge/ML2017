#include "probability.h"
#include "util.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

Probability::Probability(void)
    : scale(0.0), exp(0)
{
}

Probability::Probability(string str) {
    auto pivot = str.find('e');
    scale = stod(str.substr(0, pivot));
    exp = stol(str.substr(pivot + 1, str.length()));
}

Probability::Probability(double scale, long exp)
    : scale(scale), exp(exp)
{
}

Probability::~Probability(void) {
}

Probability& Probability::norm(void) {
    if(scale == 0.0) {
        exp = 0.0;
        return *this;
    }
    while(abs(scale) < 1) {
        scale *= 10;
        exp -= 1;
    }
    while(abs(scale) > 10) {
        scale /= 10;
        exp += 1;
    }
    return *this;
}

string Probability::str(void) const {
    stringstream stream("");
    stream << scale << "e" << exp;
    return stream.str();
}


Probability Probability::mul(const Probability& another) const {
    return Probability(scale * another.scale, exp + another.exp).norm();
}

bool Probability::gt(Probability& another) const {
    if(scale * another.scale < 0)
        return scale > 0.0;

    Probability p1 = Probability(scale, exp).norm();
    Probability p2 = Probability(another.scale, another.exp).norm();

    if(p1.exp == p2.exp)
        return p1.scale > p2.scale;

    return not ((p1.exp > p2.exp) xor (p1.scale > 0.0));
    /*
                    T                   T               T
                    T                   F               F
                    F                   T               F
                    F                   F               T
    */
}