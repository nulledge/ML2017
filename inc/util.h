#ifndef __util_h__
#define __util_h__

#include "hmm.h"
#include "probability.h"

namespace std {

    static char const * const tab = "\t";

}

static const unsigned int N_PHONES = sizeof(phones) / sizeof(hmmType);

static Probability norm_dist(Probability, double mean, double var) {
    return Probability();
}

#define SAFE_DELETE(x) if(x != nullptr) {delete(x); x = nullptr;}

#endif