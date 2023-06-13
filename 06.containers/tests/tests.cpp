#include <mycontainer.h>
#include <myarray.h>
#include <myvector.h>
#include <mylist.h> 

#include <gtest/gtest.h>
#include <iostream>


TEST(List, DISABLED_Success) {
    // Arrange
    std::cout << ">>> START TESTS <<<" << std::endl;

    const size_t expectedZeroSize = 0;

    // Assert
    EXPECT_EQ(0, expectedZeroSize);
    EXPECT_TRUE(!true);

    // list.push_back(1);
    // const size_t expectedSize = 1;

    // EXPECT_NE(list.size(), expectedZeroSize);
    // EXPECT_EQ(list.size(), expectedSize);

    // EXPECT_LE(list.size(), expectedSize);
    // EXPECT_GE(list.size(), expectedSize);
}


int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
