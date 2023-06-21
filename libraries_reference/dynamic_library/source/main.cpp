#include <dynamic_lib.h>
#include <iostream>


int main() {

    dynamic_lib::some_func();

    int a = dynamic_lib::sum(3, 2);

    std::cout << a << std::endl;

}