#include <dynamic_lib.h>
#include <iostream>


int main() {
    
    dynamic_lib::some_func();

    double a = dynamic_lib::sum(1.23, 2.34);

    std::cout << a << std::endl;

}