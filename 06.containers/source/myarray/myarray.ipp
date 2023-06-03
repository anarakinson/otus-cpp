
// add element to an arbitrary position (to the end by default)
template <typename T, size_t N>
bool static_array<T, N>::insert(const T &value, int index) {
    if (m_last >= m_cap) {
        // No free space to add one more element
        return false;
    }    
    for (size_t i = m_last; i > index; --i) {
        data_[i] = data_[i - 1];
    }
    data_[index] = value;  // add value to container
    ++m_last;
    return true;
}


// erase element by index
template <typename T, size_t N>
bool static_array<T, N>::erase(const int index) {
    if (index >= m_last) {
        // invalid value
        return false;
    }
    // need to move all element after 'pos' to one position to the left
    for (size_t i = index; i < m_last; ++i) {
        data_[i] = data_[i + 1];
    }
    --m_last;
    return true;
}


// erase elements by array of indexes   
template <typename T, size_t N>
bool static_array<T, N>::erase(size_t len_indexes, int *indexes) {
    for (int j = 0; j < len_indexes; ++j) {
        int index = indexes[j] - j;
        bool success = erase(index);
        if (!success) { return false; }
    }
    return true;
}


// delete all elements and clear allocated memory
template <typename T, size_t N>
bool static_array<T, N>::clear() {            // set all data as 0
    for (int i = 0; i < m_cap; ++i) {
        data_[i] = 0;
    }
    m_last = 0;                               // update size
    return true;
}


// copying constructor
template <typename T, size_t N>
static_array<T, N>::static_array(const static_array &other): m_last{0}, m_cap{other.capacity()} {
    if (N != other.capacity()) {
        std::cout << "Sizes not equal" << std::endl;
        return;
    }
    for (int i = 0; i < other.size(); ++i) {
        push_back(other[i]);
    }
}


// moving constructor
template <typename T, size_t N>
static_array<T, N>::static_array(static_array &&other): m_last{0}, m_cap{other.capacity()} {
    if (N != other.capacity()) {
        std::cout << "Sizes not equal" << std::endl;
        return;
    }
    for (int i = 0; i < other.size(); ++i) {
        push_back(other[i]);
    }
    other.clear();
}


// operator [] overload
template <typename T, size_t N>
T static_array<T, N>::operator [] (int index) const {
    if (index < 0 || index >= m_last) {
        // throw std::out_of_range("Container index out of range");
        std::cout << "Container index out of range" << std::endl;
        return {};
    }
    return data_[index];
}  


// copying operator = overload
template <typename T, size_t N>
static_array<T, N> &static_array<T, N>::operator = (const static_array<T, N> &other) {
    clear();
    for (int i = 0; i < other.size(); ++i) {
        push_back(other[i]);
    }
    return *this;
}


// moving operator = overload
template <typename T, size_t N>
static_array<T, N> &static_array<T, N>::operator = (static_array<T, N> &&other) {
    clear();
    for (int i = 0; i < other.size(); ++i) {
        push_back(other[i]);
    }
    other.clear();
    return *this;
}