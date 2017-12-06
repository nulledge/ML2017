#include "probability.h"

#include <cmath>

Probability::Probability(void)
    : scale(0.0), exp(0)
{
}

Probability::Probability(string str) {
    Probability();
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