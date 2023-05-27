
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


template <typename T, size_t N>
bool static_array<T, N>::erase(size_t len_indexes, int *indexes) {
    for (int j = 0; j < len_indexes; ++j) {
        int index = indexes[j] - j;
        bool success = erase(index);
        if (!success) { return false; }
    }
    return true;
}


template <typename T, size_t N>
T static_array<T, N>::operator [] (int index) const {
    if (index < 0 || index >= m_last) {
        // throw std::out_of_range("Container index out of range");
        std::cout << "Container index out of range" << std::endl;
        return {};
    }
    return data_[index];
}  
