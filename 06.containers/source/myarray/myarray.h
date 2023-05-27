#pragma once

#include <mycontainer.h> 
#include <iostream> 


template <typename T, size_t N>
class static_array : public container {
public:
    static_array(): m_last{0}, m_cap{N} {}
    ~static_array() { std::cout << "ARRAY DESTRUCTED" << std::endl; }

    bool insert(const T &value, int index);                            // add element to an arbitrary position (to the end by default)
    bool push_back(T value) { return insert(value, size()); }          // add element to the end
    bool push_forward(const T &value) { return insert(value, 0); }     // add element to the start

    bool erase(const int index);                                       // erase element by index
    bool erase(size_t len_indexes, int *indexes);                      // erase elements by array of indexes

    T operator [] (int index) const;

    size_t size() const { return m_last; }                            // return size of container
    size_t capacity() const { return m_cap; }                         // return allocated size

private: 
    T data_[N];                                                       // array to contain values
    size_t m_last;                                                    // size of counter
    size_t m_cap = N;                                                 // allocated size

};


// functions realization
#include "myarray.ipp"