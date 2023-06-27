#pragma once 


#include <vector> 

[[nodiscard]] long long int calc_fibonacci(const int index); 

class SeriesCalculator {
public:
    void put_index(const int index) { m_indexes.push_back(index); }

    [[nodiscard]] std::vector<long long int> calc() const;

private:
    std::vector<int> m_indexes;
};