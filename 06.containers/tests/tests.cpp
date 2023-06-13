#include <mycontainer.h>
#include <myarray.h>
#include <myvector.h>
#include <mylist.h> 

#include <gtest/gtest.h>
#include <iostream>


// DISABLED_
TEST(List, Success) {
    // Arrange
    std::cout << ">>> START TESTS <<<" << std::endl;

    const int expectedZeroSize = 0;

    list<int> lst{};

    // Assert
    EXPECT_EQ(lst.size(), expectedZeroSize);
    EXPECT_TRUE(true);

    lst.push_back(1);
    const size_t expectedSize = 1;

    EXPECT_NE(lst.size(), expectedZeroSize);
    EXPECT_EQ(lst.size(), expectedSize);

    EXPECT_LE(lst.size(), expectedSize);
    EXPECT_GE(lst.size(), expectedSize);
}


int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
