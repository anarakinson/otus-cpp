#include <iostream> 


void print() {
    std::cout << std::endl;
}

template <typename T>
void print(const T &t) {
    std::cout << t << std::endl;
}

template <typename T, typename... Rest>
void print(const T &first, const Rest &...rest) {
    std::cout << first << " ";
    print(rest...);
}


int main(int argc, char **argv) {

    print();
    print(1);
    print("asd", 1);
    print("hello", 123, "world", 3.14159);

}