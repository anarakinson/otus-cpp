#pragma once


template <typename T>
void run_tests(T &container);

template <typename T>
void print_container(const T &container) {
    for (size_t i = 0; i < container.size(); ++i) {
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