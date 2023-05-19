#include "percentile.h"
#include <algorithm>
#include <vector>


double Perc::eval() const {
    std::vector selection = m_selection;
    std::sort(selection.begin(), selection.end());   // sort values
    size_t count = selection.size();                 // compute number of members
    size_t place = m_perc * (count + 1) / 100;       // compute percentile 
    return selection[place - 1];                     // return member
}

void Perc::set_name(int perc) { 
    m_name = "perc" + std::to_string(perc);
}
