#pragma once 

#include <iostream>

class container {
public:
    container() {}
    virtual ~container() {}

    virtual bool push_back() { return false; }                                 // add element to the end of list
    virtual bool insert() { return false; }                                    // add element to an arbitrary position (to the end by default)
    virtual bool push_forward() { return false; }                              // add element to the start of list

    virtual bool erase() { return false; }                                     // erase element by index

    virtual size_t size() const { return 0;}                                   // return size of list (number of nodes)

//     class iterator() {
        
//     };

//     int begin() { return m_begin; }
//     int end() { return m_end; }

// private:
//     int m_begin = 0;
//     int m_end = 0;

};
