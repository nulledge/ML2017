#include "probability.h"
#include "util.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

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
    while(abs(scale) < 1) {
        scale *= 10;
        exp += 1;
    }
    while(abs(scale) > 10) {
        scale /= 10;
        exp -= 1;
    }
    return *this;
}