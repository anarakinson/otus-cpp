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

const char * Perc::name() const { 
    std::string str_name = "perc" + std::to_string(m_perc);
    char* char_array = new char[str_name.length() + 1];
    // strcpy_s(char_array, str_name.c_str());
    strcpy_s(char_array, sizeof(char_array), str_name.c_str());
    return char_array; 
}
