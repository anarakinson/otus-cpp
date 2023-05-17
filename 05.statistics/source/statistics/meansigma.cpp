#include "meansigma.h"
#include <math.h>

double Mean::compute_mean() const {
    size_t count = m_selection.size();
    double sum = 0;
    for (double x: m_selection) { sum += x; }
    return sum / count;
}

double Sigma::eval() const { 
    size_t count = m_selection.size(); 
    double mean = compute_mean();
    double var = 0;
    for (double x : m_selection) {
        var += (x - mean) * (x - mean);
    }
    double res = sqrt(var / count);
    return res;
}