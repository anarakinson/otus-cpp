#pragma once


template <typename T>
void run_tests(T &container);

template <typename T>
void print_container(const T &container) {
    for (size_t i = 0; i < container.size(); ++i) {
        // std::cout << "SUCCESS";
        // SUCCESS0 SUCCESS1 SUCCESS3 SUCCESS23 SUCCESS5 SUCCESS22 SUCCESS21 SUCCESS7 SUCCESS8 SUCCESS9 SUCCESS30 SUCCESS
        // 0 1 3 23 5 22 21 7 8 9 0 ?
        std::cout << container[i] << ' ';
    }
    std::cout << std::endl;
}

void print_separator() {
    std::cout << std::endl;
    std::cout << " ----- *** ----- " << std::endl;
    std::cout << std::endl;
}

template <typename T>
void print_size(const T &container) {
    std::cout << "size: " << container.size() << std::endl;
}
template <typename T>
void print_size(const vector<T> &container) {
    std::cout << "capacity: " << container.capacity() << "; size: " << container.size() << std::endl;
}
template <typename T, size_t N>
void print_size(const static_array<T, N> &container) {
    std::cout << "capacity: " << container.capacity() << "; size: " << container.size() << std::endl;
}


#include "utils.ipp"