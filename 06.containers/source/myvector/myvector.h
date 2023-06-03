#pragma once

#include <mycontainer.h> 
#include <iostream>

template <typename T>
class vector : public container<T> {
public:
    vector(): m_size{0}, m_cap{0} {}
    vector(const vector &other) {                                                // copying constructor
        for (int i = 0; i < other.size(); ++i) {
            push_back(other[i]);
        }
    }
    vector(vector &&other) {                                                     // moving constructor
        m_data = other.data();
        m_size = other.size();
        other.oblive();
    }
    ~vector() { 
        delete [] m_data;
        std::cout << "VECTOR DESTRUCTED" << std::endl; 
    }                                                                            // delete all elements and clear allocated memory on destruction
    
    bool insert(const T &value, int index = size()) override ;                   // add element to an arbitrary position (to the end by default)
    bool push_back(const T &value) override { return insert(value, size()); }    // add element to the end
    bool push_forward(const T &value) override { return insert(value, 0); }      // add element to the start

    bool erase(int index) override;                                                       // erase element by index
    bool erase(size_t len_indexes, int *indexes);                                // erase elements by array of indexes
    bool clear();                                                                // delete all elements and clear allocated memory
    void oblive();

    T operator [] (int index) const override;
    vector &operator = (const vector &other);
    vector &operator = (vector &&other);

    int size() const override { return m_size; }                              // return vector real size
    int capacity() const { return m_cap; }                                    // return vector memory allocated size
    T *data() { return m_data; }

private:
    T *m_data = new T[0];                                                     // vector data
    int m_size = 0;                                                           // vector real size
    int m_cap = 0;                                                            // vector capacity
};


// class functions realization
#include "myvector.ipp" 
