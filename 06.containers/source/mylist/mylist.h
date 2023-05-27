#pragma once 

#include <mycontainer.h> 
#include <iostream>

// node of the list
template <typename T>
class Node {
public:
    Node(T input): m_data{input} {}

    T data() { return m_data; }                            // return value in the node
    Node *next() { return m_next; }                        // return pointer to next node
    Node *previous() { return m_prev; }                    // return pointer to previous node
    void set_next(Node *other) { m_next = other; }         // set pointer to previous node
    void set_previous(Node *other) { m_prev = other; }     // set pointer to previous node

private:
    T m_data;                                              // stored data
    Node *m_next = nullptr;                                // pointer to next node
    Node *m_prev = nullptr;                                // pointer to previous node
};


// the list
template <typename T>
class list : public container {
public:
    list() {}
    ~list() { 
        clear(); 
        std::cout << "LIST DESTRUCTED" << std::endl; 
    }                                                        // delete all elements and clear allocated memory on destruction

    bool push_back(T value);                                 // add element to the end of list
    bool insert(T value, int index = size());                // add element to an arbitrary position (to the end by default)
    bool push_forward(T value) { return insert(value, 0); }  // add element to the start of list

    Node<T> *iterate(int index) const;                       // iterate elements of the list
    bool erase(int index);                                   // erase element by index
    bool erase(size_t len_indexes, int *indexes);            // erase elements by array of indexes

    bool clear();                                            // delete all elements and clear allocated memory

    T operator [] (int index) const;

    size_t size() const { return m_size; }                   // return size of list (number of nodes)

private:
    int m_size = 0;                                          // size of list (number of nodes)
    Node<T> *m_begin = nullptr;                              // pointer to the first node
    Node<T> *m_end = nullptr;                                // pointer to the last node
};



// class functions realization
#include "mylist.ipp"