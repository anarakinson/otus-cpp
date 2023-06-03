#pragma once

#include <mycontainer.h> 
#include <iostream> 


template <typename T, size_t N>
class static_array : public container<T> {
public:
    static_array(): m_last{0}, m_cap{N} {}
    static_array(const static_array &other);                                    // copying constructor
    static_array(static_array &&other);                                         // moving constructor
    ~static_array() { std::cout << "ARRAY DESTRUCTED" << std::endl; }

    bool insert(const T &value, int index) override;                            // add element to an arbitrary position (to the end by default)
    bool push_back(const T &value) override { return insert(value, size()); }   // add element to the end
    bool push_forward(const T &value) override { return insert(value, 0); }     // add element to the start

    bool erase(const int index) override;                                       // erase element by index
    bool erase(size_t len_indexes, int *indexes);                               // erase elements by array of indexes    
    bool clear();                                                               // delete all elements and clear allocated memory

    T operator [] (int index) const override;
    static_array &operator = (const static_array &other);
    static_array &operator = (static_array &&other);

    int size() const override { return m_last; }                             // return size of container
    int capacity() const { return m_cap; }                                   // return allocated size

private: 
    T data_[N];                                                              // array to contain values
    int m_last;                                                              // size of counter
    int m_cap = N;                                                           // allocated size

};


// functions realization
#include "myarray.ipp"