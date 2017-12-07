#ifndef __util_h__
#define __util_h__

#include "hmm.h"
#include "probability.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace std {

    static char const * const tab = "\t";

}

static const unsigned int N_PHONES = sizeof(phones) / sizeof(hmmType);

static Probability norm_dist(Probability prob, double mean, double var) {
    return Probability(
        exp(- pow(prob.scale * exp(prob.exp) - mean, 2) / (2.0 * var) ) / sqrt(2.0 * M_PI * var)
    );
}

#define SAFE_DELETE(x) if(x != nullptr) {delete(x); x = nullptr;}

#endif