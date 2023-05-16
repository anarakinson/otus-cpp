#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>



void fill_vector(std::vector<int> &values, size_t count) {
	values.resize(count);
	for (size_t i = 0; i < count; ++i) {
		values[i] = static_cast<int>(i);
	}
}


template <typename T>
void make_random_shuffle(std::vector<T> &values) {

    // chrono system clock
    auto seconds_count = std::chrono::system_clock::now().time_since_epoch().count();
    std::cout << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
    unsigned int seed = static_cast<unsigned int>(seconds_count);
    // random engine
    std::default_random_engine engine{seed};
    // algorithm shuffle
    std::shuffle(values.begin(), values.end(), engine);

}




void run_test_suite(size_t iteration_count) {

    const size_t elements_count = 100000;
    std::vector<int> values;

    fill_vector(values, elements_count);
    make_random_shuffle(values);


    std::cout << "iteration count: " << iteration_count << std::endl;

    {
        auto start_time = std::chrono::system_clock::now();
        for (size_t i = 0; i < iteration_count; ++i) {
            std::vector<int> test_data = values;
            std::sort(test_data.begin(), test_data.end());
        }
        auto end_time = std::chrono::system_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "std::sort duration = " << milliseconds.count() << "ms" << std::endl;
        std::cout << "std::sort avg = " << milliseconds.count() / iteration_count << "ms" << std::endl;
    }


    {
        auto start_time = std::chrono::system_clock::now();
        for (size_t i = 0; i < iteration_count; ++i) {
            std::vector<int> test_data = values;
            std::qsort(
                test_data.data(), 
                test_data.size(),
                sizeof(int),
                [](const void *x, const void *y) {
                    const int arg1 = *static_cast<const int *>(x);
                    const int arg2 = *static_cast<const int *>(y);
                    if (arg1 > arg2) { return 1; }
                    else if (arg1 < arg2) { return -1; }
                    return 0;
                }
            );
        }
        auto end_time = std::chrono::system_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "std::sort duration = " << milliseconds.count() << "ms" << std::endl;
        std::cout << "std::sort avg = " << milliseconds.count() / iteration_count << "ms" << std::endl;
    }

}



int main() {
    std::vector<int> vec{};
    fill_vector(vec, 10);

    make_random_shuffle(vec);

    for (int val : vec) {
        std::cout << val << std::endl;
    }

    run_test_suite(10);
}