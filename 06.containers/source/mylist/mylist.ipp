
// add element to an arbitrary position (to the end by default)
template <typename T>
bool list<T>::push_back(T value) {
    Node<T> *node = new Node<T>{value};          // create new node
    if (m_begin == nullptr) {                    // if list empty - just add node
        m_begin = node;   
    } else if (m_end == nullptr) {               // if list have only one node
        m_end = node;                            // add node to the end of list
        m_end->set_previous(m_begin);            // set pointer from last member to first
        m_begin->set_next(m_end);                // and vice versa
    } else {
        node->set_previous(m_end);               // set pointer from new node to last member
        m_end->set_next(node);                   // set pointer from last member to new node
        m_end = node;                            // make new node the last one
    }
    m_size++;                                    // update size 
    return true;
}


// add element to an arbitrary position (to the end by default)
template <typename T>
bool list<T>::insert(T value, int index) {
    if (m_begin == nullptr || index == size()) {  // if list is empty - just push_back or insert to the end
        push_back(value);
        return true;
    }

    Node<T> *node = new Node<T>{value};           // create new node
    Node<T> *next_node = iterate(index);          // find node by index
    Node<T> *prev_node = next_node->previous();   // find previous node

    node->set_previous(prev_node);                // insert new node between finded node and previous one
    node->set_next(next_node);                    // and set pointers between every node

    if (prev_node != nullptr) {
        prev_node->set_next(node);
    } else {                                      // if finded node is the first one
        m_begin = node;                           // set new node as first
    }

    m_size++;                                     // update size
    return true;
}


// iterate elements of the list
template <typename T>
Node<T> *list<T>::iterate(int index) const {
    if (m_begin == nullptr || index < 0 || index >= m_size) {
        throw std::out_of_range("Container index out of range");  // check if index is correct
    }
    Node<T> *node = m_begin;
    for (int i = 0; i < index; ++i) {            // iterate nodes until find the right one
        node = node->next();
    }
    return node;
}


// erase element by index
template <typename T>
bool list<T>::erase(int index) {
    Node<T> *node = iterate(index);               // iterate nodes until find the right one
    Node<T> *prev_node = node->previous();        // find next and previous nodes
    Node<T> *next_node = node->next();
    
    if (prev_node != nullptr) {                   // set pointers from previous to next and vice versa
        prev_node->set_next(next_node);
    } else {
        m_begin = next_node;
    }
    if (next_node != nullptr) {
        next_node->set_previous(prev_node);
    } else {
        m_end = prev_node;
    }
    delete node;                                   // delete finded node
    m_size--;                                      // update size
    return true;
}


// erase element by several indexes
template <typename T>
bool list<T>::erase(size_t len_indexes, int *indexes) {
    for (int j = 0; j < len_indexes; ++j) {
        int index = indexes[j] - j;
        bool success = erase(index);
        if (!success) { return false; }
    }
    return true;
}


// delete all elements and clear allocated memory
template <typename T> 
bool list<T>::clear() {
    if (m_size == 0) { return true; }                     // if list empty - nothing to do
    else if (m_begin == nullptr) {                        // if size = 0 and begin = 0 -> something wrong
        std::cout << "Something wrong" << std::endl;
        return false;
    }
    Node<T> *node = m_begin;                              // start from begin
    while (true) {
        Node<T> *node = m_begin->next();                  // get next node and delete current
        delete m_begin;
        m_size--;                                         // update size
        if (node == m_end) {                              // if current node is the last one
            delete m_end;                                 // delete it
            m_size--;                                     // update size
            break;                                        // and finish
        }
        m_begin = node;                                   // set current node as first
    }
    return true;
}


// operator [] overload
template <typename T>
T list<T>::operator [] (int index) const {
    if (index < 0 || index >= m_size) {
        // throw std::out_of_range("Container index out of range");
        std::cout << "Container index out of range" << std::endl;
        return {};
    }
    Node<T> *node = iterate(index);                // iterate nodes until find the right one
    T data = node->data();                         // get stored value
    return data;
}
