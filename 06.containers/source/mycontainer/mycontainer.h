#pragma once 

#include <iostream>


template <typename T>
class container {
public:
    container() {}  
    virtual ~container() {}

    virtual bool insert(const T &value, int index) { return false; }           // add element to an arbitrary position (to the end by default)
    virtual bool push_back(const T &value) { return false; }                   // add element to the end of list
    virtual bool push_forward(const T &value) { return false; }                // add element to the start of list

    virtual bool erase(const int index) { return false; }                      // erase element by index

    virtual T operator [] (int index) const { return {}; } 

    virtual size_t size() const { return 0;}                                   // return size of list (number of nodes)

};
