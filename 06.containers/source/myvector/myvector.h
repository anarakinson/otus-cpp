#pragma once

#include <mycontainer.h> 
#include <iostream>

template <typename T>
class vector : public container {
public:
    vector(): m_size{0}, m_cap{0} {}
    ~vector() { 
        delete [] m_data;
        std::cout << "VECTOR DESTRUCTED" << std::endl; 
    }                                                           // delete all elements and clear allocated memory on destruction
    
    bool insert(T value, int index = size());                   // add element to an arbitrary position (to the end by default)
    bool push_back(T value) { return insert(value, size()); }   // add element to the end
    bool push_forward(T value) { return insert(value, 0); }     // add element to the start
    bool erase(int index);                                      // erase element by index
    bool erase(size_t len_indexes, int *indexes);               // erase elements by array of indexes

    bool clear();                                               // delete all elements and clear allocated memory

    T operator [] (int index) const;

    size_t capacity() const { return m_cap; }                            // return vector memory allocated size
    size_t size() const { return m_size; }                               // return vector real size

private:
    T *m_data = new T[0];                                       // vector data
    size_t m_size = 0;                                          // vector real size
    size_t m_cap = 0;                                           // vector capacity
};


// class functions realization
#include "myvector.ipp" 
