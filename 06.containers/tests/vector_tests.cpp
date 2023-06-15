#include <mycontainer.h>
#include <myvector.h>

#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>



class VectorFixture : public testing::Test {
public:
    
    const size_t testing_size = 10;
    vector<int> test_vector;
    
    static void SetUpTestSuite() {
        std::cout << "Vector SetUpTestSuite" << std::endl;
    }

    static void TearDownTestSuite() {
        std::cout << "Vector TearDownTestSuite" << std::endl;
    }

    void SetUp() override { 
        std::cout << "SetUp" << std::endl;

        // Create vector with testing_size elements
        for (int i = 0; i < testing_size; ++i) 
            test_vector.push_back(i);
    }

    void TearDown() override {
        std::cout << "TearDown" << std::endl;
        test_vector.clear();
    }


};


// DISABLED_
// 1 test
TEST(Vector, Basic_Test) {
    // Arrange
    const int expected_zero_size = 0;

    vector<int> vec{};

    // Assert
    EXPECT_EQ(vec.size(), expected_zero_size);

    vec.push_back(1);
    const size_t expected_size = 1;

    EXPECT_NE(vec.size(), expected_zero_size);
    EXPECT_EQ(vec.size(), expected_size);
}


// 2 test
TEST(Vector, Copying_Constructor) {
    // Arrange
    vector<int> vec{};

    for (int i = 0; i < 10000; i += 1000) {
        vec.push_back(i);
    }

    // Act
    vector<int> new_vec = vec;

    // Assert
    EXPECT_EQ(vec.size(), new_vec.size());                        // Equal sizes
    EXPECT_EQ(vec[0], new_vec[0]);
    EXPECT_EQ(vec[vec.size() - 1], new_vec[new_vec.size() - 1]);  // Equal last elements

    vec.push_back(1);

    EXPECT_NE(vec.size(), new_vec.size());                        // Non equal sizes
    EXPECT_NE(vec[vec.size() - 1], new_vec[new_vec.size() - 1]);  // Non equal last element
    EXPECT_GE(vec.size(), new_vec.size());
}


// 3 test
TEST(Vector, Moving_Constructor) {
    // Arrange
    vector<int> vec{};

    for (int i = 0; i < 10000; i += 1000) {
        vec.push_back(i);
    }
    int vec_size = vec.size();
    int last_element = vec[vec.size() - 1];
    int first_element = vec[0];


    // Act
    vector<int> new_vec = std::move(vec);

    // Assert
    EXPECT_EQ(new_vec.size(), vec_size);                          // Equal sizes
    EXPECT_EQ(new_vec[0], first_element); 
    EXPECT_EQ(new_vec[new_vec.size() - 1], last_element);         // Equal last elements

    new_vec.push_back(1);

    EXPECT_NE(new_vec.size(), vec_size);                          // Non equal sizes
    EXPECT_NE(new_vec[new_vec.size() - 1], last_element);         // Non equal last element
}


// 4 test
TEST(Vector, Expected_Sequence_Push_Back) {                           // Push back values nd assert it
    // Arrange
    int expected_sequence[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> vec{};

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }
    
    // Act
    
    // Assert
    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], expected_sequence[i]);                         // Equal element        
    }

}


// 5 test
TEST(Vector, Expected_Sequence_Push_Forward) {                           // Push forward values nd assert it
    // Arrange
    int expected_sequence[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    vector<int> vec{};

    for (int i = 0; i < 10; ++i) {
        vec.push_forward(i);
    }
    
    // Act
    
    // Assert
    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], expected_sequence[i]);                          // Equal element        
    }

}


// 6 test
TEST(Vector, Forward_Middle_Back_Insertions) {
    // Arrange
    int expected_sequence[10] = {10, 0, 1, 3, 20, 5, 7, 8, 9, 30};
    const int LEN_IDX = 3; 
    int indexes[LEN_IDX] = {2, 4, 6};

    vector<int> vec{};

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }
    
    // Act
    vec.erase(LEN_IDX, indexes);                                          // Erase 2, 4, 6 - counting from zero
    vec.push_forward(10);
    vec.insert(20, vec.size() / 2);                                       // insert to the middle
    vec.push_back(30);

    // Assert
    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], expected_sequence[i]);                          // Equal element        
    }

    EXPECT_EQ(vec[0], 10);                                                // Equal first element
    EXPECT_EQ(vec[vec.size() / 2 - 1], 20);                               // Equal middle element
    EXPECT_EQ(vec[vec.size() - 1], 30);                                   // Equal last element

}


// 7 test
TEST_F(VectorFixture, Inserting_And_Erasing) {
    // Arrange
    int expected_sequence[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int zero_num = 21;
    int last_num = 22;
    int first_num = 23;
    int ten_num = 24;
    
    
    // Act
    test_vector.insert(zero_num, 0);
    test_vector.insert(last_num, test_vector.size());
    test_vector.insert(first_num, 1);
    test_vector.insert(ten_num, 10);

    // Assert
    ASSERT_EQ(test_vector.size(), 14);
    ASSERT_EQ(test_vector[test_vector.size() - 1], last_num);
    ASSERT_EQ(test_vector[0], zero_num);
    ASSERT_EQ(test_vector[1], first_num);
    ASSERT_EQ(test_vector[10], ten_num);
    
    // Act again
    test_vector.erase(10);                                                      // return vector to start state
    test_vector.erase(0);
    test_vector.erase(0);
    test_vector.erase(test_vector.size() - 1);

    // Assert again
    ASSERT_EQ(test_vector.size(), 10);
    for (int i = 0; i < test_vector.size(); ++i) {
        EXPECT_EQ(test_vector[i], expected_sequence[i]);                        // Equal element        
    }
}


// 8 test
TEST_F(VectorFixture, Erase_All) {
    // Arrange
    // nothing to do here, because we have fixture
    
    // Act
    for (int i = test_vector.size() - 1; i >= 0; --i)
        test_vector.erase(i);

    // Assert
    ASSERT_EQ(test_vector.size(), 0);
}


// 9 test
TEST_F(VectorFixture, Push_Back_Forward_Insert) {
    // Arrange
    int back_number = 7;
    int forward_number = 123;
    int insert_number = 1991;
    int insert_placement = 6;
    
    // Act
    test_vector.push_back(back_number);
    test_vector.push_forward(forward_number);
    test_vector.insert(insert_number, insert_placement);

    // Assert
    ASSERT_EQ(test_vector[0], forward_number);
    ASSERT_EQ(test_vector[test_vector.size() - 1], back_number);
    ASSERT_EQ(test_vector[insert_placement], insert_number);
    ASSERT_EQ(test_vector.size(), 13);
}


// 10 test
TEST_F(VectorFixture, Lost_Element_Check) {
    // Arrange

    // Act

    // Assert
    ASSERT_FALSE(test_vector[-1]);
    ASSERT_FALSE(test_vector[123]);
}

