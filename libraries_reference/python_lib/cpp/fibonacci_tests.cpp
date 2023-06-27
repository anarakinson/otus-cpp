#include "fibonacci.h"

#include <gtest/gtest.h>


TEST(Fibonacci, calc_small) {
    EXPECT_EQ(55, calc_fibonacci(10));
    EXPECT_EQ(6765, calc_fibonacci(20));
}

TEST(Fibonacci, calc_big) {
    EXPECT_EQ(1134903170, calc_fibonacci(45));
}

TEST(Fibonacci, Series) {
    const std::vector<long long int> expected = {0, 5, 55};

    SeriesCalculator calc{};

    calc.put_index(0);
    calc.put_index(5);
    calc.put_index(10);
    
    EXPECT_EQ(expected, calc.calc());
}

