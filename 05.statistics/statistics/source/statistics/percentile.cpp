#include "percentile.h"
#include <algorithm>
#include <vector>


double Perc::eval() const {
    std::vector selection = m_selection;
    std::sort(selection.begin(), selection.end());
    size_t count = selection.size();
    size_t place = m_perc * (count + 1) / 100;
    return selection[place - 1];
}