#include "meansigma.h"
#include <math.h>


double Mean::compute_mean() const {
    size_t count = m_selection.size();        // compute count
    double sum = 0;
    for (double x: m_selection) { sum += x; } // compute sum of members
    return sum / count;                       // compute mean
}

double Sigma::eval() const { 
    size_t count = m_selection.size();  // compute count
    double mean = compute_mean();       // compute mean
    double var = 0;                     // compute variance
    for (double x : m_selection) {
        var += (x - mean) * (x - mean);
    }
    double res = sqrt(var / count);     // compute standard deviation
    return res;
}