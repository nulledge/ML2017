#include "probability.h"

Probability::Probability(void)
    : scale(0.0), exp(0)
{
}

Probability::Probability(double scale, long exp)
    : scale(scale), exp(exp)
{
}

Probability::~Probability(void) {
}