#include <gtest/gtest.h>
#include <iostream>


TEST(VCPKG, Basic_Test) {
    // Arrange
    const int expectedZeroSize = 0;

    // Assert
    EXPECT_EQ(0, expectedZeroSize);

    EXPECT_FALSE(false);
}


int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
