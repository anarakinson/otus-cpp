#include <mycontainer.h>
#include <myarray.h>

#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>


// DISABLED_
constexpr size_t arr_size = 20;


class ArrayFixture : public testing::Test {
public:
    
    const size_t testing_size = 10;
    static_array<int, arr_size> test_array{};
    
    static void SetUpTestSuite() {
        std::cout << "Array SetUpTestSuite" << std::endl;
    }

    static void TearDownTestSuite() {
        std::cout << "Array TearDownTestSuite" << std::endl;
    }

    void SetUp() override { 
        std::cout << "SetUp" << std::endl;

        // Create static_array with testing_size elements
        for (int i = 0; i < testing_size; ++i) 
            test_array.push_back(i);
    }

    void TearDown() override {
        std::cout << "TearDown" << std::endl;
        test_array.clear();
    }


};


// DISABLED_
// 1 test
TEST(Array, Basic_Test) {
    // Arrange
    const int expected_zero_size = 0;
    
    static_array<int, arr_size> arr{};

    // Assert
    EXPECT_EQ(arr.size(), expected_zero_size);

    arr.push_back(1);
    const size_t expected_size = 1;

    EXPECT_NE(arr.size(), expected_zero_size);
    EXPECT_EQ(arr.size(), expected_size);
}


// 2 test
TEST(Array, Copying_Constructor) {
    // Arrange
    
    static_array<int, arr_size> arr{};

    for (int i = 0; i < 10000; i += 1000) {
        arr.push_back(i);
    }

    // Act
    static_array<int, arr_size> new_arr = arr;

    // Assert
    EXPECT_EQ(arr.size(), new_arr.size());                        // Equal sizes
    EXPECT_EQ(arr[0], new_arr[0]);
    EXPECT_EQ(arr[arr.size() - 1], new_arr[new_arr.size() - 1]);  // Equal last elements

    arr.push_back(1);

    EXPECT_NE(arr.size(), new_arr.size());                        // Non equal sizes
    EXPECT_NE(arr[arr.size() - 1], new_arr[new_arr.size() - 1]);  // Non equal last element
    EXPECT_GE(arr.size(), new_arr.size());
}


// 3 test
TEST(Array, Moving_Constructor) {
    // Arrange
    
    static_array<int, arr_size> arr{};

    for (int i = 0; i < 10000; i += 1000) {
        arr.push_back(i);
    }
    int expected_size = arr.size();
    int last_element = arr[arr.size() - 1];
    int first_element = arr[0];


    // Act
    static_array<int, arr_size> new_arr = std::move(arr);

    // Assert
    EXPECT_EQ(new_arr.size(), expected_size);                          // Equal sizes
    EXPECT_EQ(new_arr[0], first_element); 
    EXPECT_EQ(new_arr[new_arr.size() - 1], last_element);         // Equal last elements

    new_arr.push_back(1);

    EXPECT_NE(new_arr.size(), expected_size);                          // Non equal sizes
    EXPECT_NE(new_arr[new_arr.size() - 1], last_element);         // Non equal last element
}


// 4 test
TEST(Array, Expected_Sequence_Push_Back) {
    // Arrange
    int expected_sequence[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    static_array<int, arr_size> arr{};

    for (int i = 0; i < 10; ++i) {
        arr.push_back(i);
    }
    
    // Act
    
    // Assert
    for (int i = 0; i < arr.size(); ++i) {
        EXPECT_EQ(arr[i], expected_sequence[i]);                          // Equal element        
    }

}


// 5 test
TEST(Array, Expected_Sequence_Push_Forward) {
    // Arrange
    int expected_sequence[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    
    static_array<int, arr_size> arr{};

    for (int i = 0; i < 10; ++i) {
        arr.push_forward(i);
    }
    
    // Act
    
    // Assert
    for (int i = 0; i < arr.size(); ++i) {
        EXPECT_EQ(arr[i], expected_sequence[i]);                          // Equal element        
    }

}


// 6 test
TEST(Array, Forward_Middle_Back_Insertions) {
    // Arrange
    int expected_sequence[10] = {10, 0, 1, 3, 20, 5, 7, 8, 9, 30};
    const int LEN_IDX = 3; 
    int indexes[LEN_IDX] = {2, 4, 6};

    
    static_array<int, arr_size> arr{};

    for (int i = 0; i < 10; ++i) {
        arr.push_back(i);
    }
    
    // Act
    arr.erase(LEN_IDX, indexes);                                          // Erase 2, 4, 6 - counting from zero
    arr.push_forward(10);
    arr.insert(20, arr.size() / 2);                                       // insert to the middle
    arr.push_back(30);

    // Assert
    for (int i = 0; i < arr.size(); ++i) {
        EXPECT_EQ(arr[i], expected_sequence[i]);                          // Equal element        
    }

    EXPECT_EQ(arr[0], 10);                                                // Equal first element
    EXPECT_EQ(arr[arr.size() / 2 - 1], 20);                               // Equal middle element
    EXPECT_EQ(arr[arr.size() - 1], 30);                                   // Equal last element

}


// 7 test
TEST_F(ArrayFixture, Inserting_And_Erasing) {
    // Arrange
    int expected_sequence[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int zero_num = 21;
    int last_num = 22;
    int first_num = 23;
    int ten_num = 24;
    
    
    // Act
    test_array.insert(zero_num, 0);
    test_array.insert(last_num, test_array.size());
    test_array.insert(first_num, 1);
    test_array.insert(ten_num, 10);

    // Assert
    ASSERT_EQ(test_array.size(), 14);
    ASSERT_EQ(test_array[test_array.size() - 1], last_num);
    ASSERT_EQ(test_array[0], zero_num);
    ASSERT_EQ(test_array[1], first_num);
    ASSERT_EQ(test_array[10], ten_num);
    
    // Act again
    test_array.erase(10);                                                      // return static_array to start state
    test_array.erase(0);
    test_array.erase(0);
    test_array.erase(test_array.size() - 1);

    // Assert again
    ASSERT_EQ(test_array.size(), 10);
    for (int i = 0; i < test_array.size(); ++i) {
        EXPECT_EQ(test_array[i], expected_sequence[i]);                        // Equal element        
    }
}


// 8 test
TEST_F(ArrayFixture, Erase_All) {
    // Arrange
    // nothing to do here, because we have fixture
    
    // Act
    for (int i = test_array.size() - 1; i >= 0; --i)
        test_array.erase(i);

    // Assert
    ASSERT_EQ(test_array.size(), 0);
}


// 9 test
TEST_F(ArrayFixture, Push_Back_Forward_Insert) {
    // Arrange
    int back_number = 7;
    int forward_number = 123;
    int insert_number = 1991;
    int insert_placement = 6;
    
    // Act
    test_array.push_back(back_number);
    test_array.push_forward(forward_number);
    test_array.insert(insert_number, insert_placement);

    // Assert
    ASSERT_EQ(test_array[0], forward_number);
    ASSERT_EQ(test_array[test_array.size() - 1], back_number);
    ASSERT_EQ(test_array[insert_placement], insert_number);
    ASSERT_EQ(test_array.size(), 13);
}


// 10 test
TEST_F(ArrayFixture, Lost_Element_Check) {
    // Arrange

    // Act

    // Assert
    ASSERT_FALSE(test_array[-1]);
    ASSERT_FALSE(test_array[123]);
}

