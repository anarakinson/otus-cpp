#include <mylist.h>
#include <myvector.h>
#include <myarray.h>
#include <utils.h>

#include <iostream>

int main() {

    print_separator();

    std::cout << "Test 0: Static array\n" << std::endl;
    static_array<double, 15> arr{};
    run_tests(arr);

    print_separator();

    std::cout << "Test 1: List\n" << std::endl;
    list<double> lst{};
    run_tests(lst);
    lst.clear();
    print_size(lst);

    print_separator();

    std::cout << "Test 2: Vector\n" << std::endl;
    vector<double> vec{};
    run_tests(vec);
    vec.clear();
    print_size(vec);

    std::cout << std::endl;

}
