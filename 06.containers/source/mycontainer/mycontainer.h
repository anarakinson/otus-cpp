#pragma once 

#include <iostream>


template <typename T>
class container {
public:
    container() {}  
    virtual ~container() {}

    virtual bool insert(const T &value, int index) = 0;           // add element to an arbitrary position (to the end by default)
    virtual bool push_back(const T &value) = 0;                   // add element to the end of list
    virtual bool push_forward(const T &value) = 0;                // add element to the start of list

    virtual bool erase(const int index) = 0;                      // erase element by index

    virtual T operator [] (int index) const = 0;

    virtual int size() const = 0;                                 // return size of list (number of nodes)

};
