
// add element to an arbitrary position (to the end by default)
template <typename T>
bool vector<T>::insert(const T &value, int index) {
    if (m_cap <= m_size) {                        // if vector is full
        int addition = 10;
        if (m_cap < 20) { addition = m_cap / 2 + 1; }
        T *new_data = new T[m_cap + addition];    // create new memory region
        for (size_t i = 0; i < m_cap; ++i) {
            size_t idx = i;
            if (i >= index) { idx = i + 1; }
            new_data[idx] = m_data[i];            // copying elements
        }
        new_data[index] = value;                  // add new element
        delete [] m_data;                         // delete old memory region
        m_data = new_data;                        // update data
        m_cap += addition;                        // update capacity
    } else {                                      // if vector is not full
        for (size_t i = m_size; i > index; --i) {
            size_t idx = i - 1;
            m_data[i] = m_data[idx];              // copying elements
        }
        m_data[index] = value;                    // add new element
    }
    m_size++;                                     // update size
    return true;
}


// erase element by index
template <typename T>
bool vector<T>::erase(int index) {
    if (index < 0 || index >= m_size) {           // if index incorrect throw error
        throw std::out_of_range("Container index out of range");
    }
    for (size_t i = index + 1; i < m_cap; ++i) {
        size_t idx = i - 1;
        m_data[idx] = m_data[i];                  // copying elements
    }
    m_size--;                                     // update size
    if (m_cap / 2 > m_size) {                     // if twice as much memory is allocated, than needed
        T *new_data = new T[m_size + 1];          // create new memory region
        for (size_t i = 0; i < m_size; ++i) {
            size_t idx = i;
            if (i >= index) { idx = i + 1; }
            new_data[idx] = m_data[i];            // copying elements
        }
        delete [] m_data;                         // delete old memory region
        m_data = new_data;                        // update data
        m_cap = m_size + 1;                       // update capacity
    }
    return true;
}


// erase element by several indexes
template <typename T>
bool vector<T>::erase(size_t len_indexes, int *indexes) {
    for (int j = 0; j < len_indexes; ++j) {
        int index = indexes[j] - j;
        bool success = erase(index);
        if (!success) { return false; }
    }
    return true;
}


// delete all elements and clear allocated memory and allocate new region
template <typename T>
bool vector<T>::clear() {
    delete [] m_data;                         // delete old memory region
    m_data = new T[0];                        // allocate new empty region
    m_cap = 0;                                // update size and capacity
    m_size = 0;
    return true;
}


// operator [] overload
template <typename T>
T vector<T>::operator [] (int index) const {
    if (index < 0 || index >= m_size) {         // if index incorrect throw error
        // throw std::out_of_range("Container index out of range");
        std::cout << "Container index out of range" << std::endl;
        return {};
    }
    return m_data[index];                       // return value
}  


// operator = overload
template <typename T>
vector<T> &vector<T>::operator = (const vector<T> &other) {             
    clear();
    for (int i = 0; i < other.size(); ++i) {
        push_back(other[i]);
    }
    return *this;
}


// moving operator = overload
template <typename T>
vector<T> &vector<T>::operator = (vector<T> &&other) {             
    clear();
    m_data = other.data();
    m_size = other.size();
    m_cap = other.capacity();
    other.oblive();
    return *this;
}


// erase all info from list without erasing elements
template <typename T>
void vector<T>::oblive() {
    m_data = new T[0];
    m_size = 0;
    m_cap = 0;
}