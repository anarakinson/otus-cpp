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

const char * Perc::name() const { 
    std::string str_name = "perc" + std::to_string(m_perc);  // "perc" + percentile value
    char* char_array = new char[str_name.length() + 1];      // cast to char array
    // strcpy_s(char_array, str_name.c_str());
    strcpy_s(char_array, sizeof(char_array), str_name.c_str());
    return char_array; 
}
