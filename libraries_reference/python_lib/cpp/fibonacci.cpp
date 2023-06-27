#include "fibonacci.h" 


long long int calc_fibonacci(const int index) {
    
    if (index <= 1) {
        return index;
    }

    // return calc_fibonacci(index - 1) + calc_fibonacci(index - 2);

    long long int a = 1, b = 0;
    long long int result = 0;
    
    for (int i = 0; i < (index - 1); ++i) {
        result = a + b;
        b = a;
        a = result;
    }

    return result;

}


std::vector<long long int> SeriesCalculator::calc() const {
    
    std::vector<long long int> result;
    result.reserve(m_indexes.size());

    for (const auto &index : m_indexes) {
        result.push_back(calc_fibonacci(index));
    } 

    return result;

}
