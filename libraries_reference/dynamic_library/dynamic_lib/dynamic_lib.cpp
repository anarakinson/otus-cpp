#include "dynamic_lib.h"

#include <iostream>

namespace dynamic_lib {

    void some_func() {
        std::cout << "Dynamic lib function starts:" << std::endl;
        std::cout << "La la la la la" << std::endl;
        std::cout << "Dynamic lib function ends." << std::endl;
    }

    int sum(int a, int b) {
        return a + b;
    }

    double sum(double a, double b) {
        return a + b;
    }

} // namespace static_lib