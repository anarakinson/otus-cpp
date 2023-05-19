#include "meansigma.h"
#include <math.h>


double Mean::compute_mean() const {
    return m_sum / counter;                       // compute mean
}

double Sigma::eval() const { 
    double mean = compute_mean();       // compute mean
    double var = 0;                     // compute variance
    for (double x : m_selection) {
        var += (x - mean) * (x - mean);
    }
    double res = sqrt(var / counter);     // compute standard deviation
    return res;