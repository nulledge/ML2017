#include "cell.h"
#include "util.h"

#include <iostream>

Cell::Cell(void) {}
Cell::~Cell(void) {}

long double Cell::observe(const MFCC* mfcc, const unsigned int step) {
    long double* observed = mfcc->_data[step];
    long double result = 1.0;
    for(auto it_dim = 0U; it_dim < N_DIMENSION; it_dim ++) {
        long double inter = 0.0;
        for(auto it_pdf = 0U; it_pdf < N_PDF; it_pdf ++) {
            const auto& weight = _out->pdf[it_pdf].weight;
            const auto& mean = _out->pdf[it_pdf].mean[it_dim];
            const auto& var = _out->pdf[it_pdf].var[it_dim];
            
            inter += weight * norm_dist(observed[it_dim], mean, var);
        }
        result *= inter;
    }
    return result;
}