
template <typename T>
void run_tests(T &container) {

    std::cout << "Fill container:" << std::endl;
    
    for (int i = 0; i < 10; ++i) {
        container.push_back(i);
    }
    print_container(container);
    print_size(container);
    std::cout << std::endl;

    /* ----- *** ----- */
    std::cout << "Erase 3, 5, 7 indexes (2, 4, 6 - counting from zero):" << std::endl;
    
    const int LEN_IDX = 3; 
    int indexes[LEN_IDX] = {2, 4, 6};
    container.erase(LEN_IDX, indexes);
    print_container(container);
    print_size(container);
    std::cout << std::endl;

    /* ----- *** ----- */
    std::cout << "Push forward '10':" << std::endl;
    
    container.push_forward(10);
    print_container(container);
    std::cout << std::endl;

    /* ----- *** ----- */
    std::cout << "Insert '20' to the middle:" << std::endl;
    
    container.insert(20, container.size() / 2);
    print_container(container);
    std::cout << std::endl;

    /* ----- *** ----- */
    std::cout << "Push back '30':" << std::endl;
    
    container.push_back(30);
    print_container(container);
    print_size(container);
    std::cout << std::endl;

    /* ----- *** ----- */
    std::cout << "Show first and last elements by index:" << std::endl;
    std::cout << "first: " << container[0]
              << "; last: " << container[container.size() - 1] << std::endl;
    std::cout << std::endl;

    /* ----- *** ----- */
    std::cout << "Try to show index out of range:" << std::endl;
    std::cout << container[-1] << std::endl;
    std::cout << std::endl;

    /* ----- *** ----- */
    std::cout << "Push back '32':" << std::endl;
    
    container.insert(32, container.size());
    print_container(container);
    std::cout << std::endl;

    /* ----- *** ----- */
    std::cout << "Erase first and last elements:" << std::endl;
    
    container.erase(0);
    container.erase(container.size() - 1);
    print_container(container);
    print_size(container);
    std::cout << std::endl;



    /* ----- *** ----- */
    std::cout << "Insert '20' to the middle:" << std::endl;
    
    // container.insert(21, (container.size() / 2) + 1);
    // container.insert(22, (container.size() / 2));
    // container.insert(23, (container.size() / 2) - 1);
    container.insert(222, 4);
    container.insert(223, 4);
    container.insert(224, 4);
    container.insert(225, 4);
    print_container(container);
    std::cout << std::endl;



}
