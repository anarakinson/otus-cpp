#pragma once 

#include <exception>
#include <iostream>
#include <utility>
#include <mutex>
#include <vector>
#include <thread>
#include <cassert>


template <class T>
class monitor {
public:
    template <typename... Args>
    monitor(Args &&...args) : m_data{std::forward<Args>(args)...} {}

    struct helper {
        helper(monitor *mon) 
            : m_parent{mon}
            , m_lock{mon->m_mutex} {}
        
        T *operator->() {
            return &m_parent->m_data; 
        }
    private:
        monitor *m_parent;
        std::lock_guard<std::mutex> m_lock;
    };

    helper operator->() { return helper(this); }

private:
    T m_data;
    std::mutex m_mutex;
};
