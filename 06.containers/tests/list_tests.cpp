#include <mycontainer.h>
#include <mylist.h> 

#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>



class ListFixture : public testing::Test {
public:
    
    const size_t testing_size = 10;
    list<int> test_list;

    static void SetUpTestSuite() {
        std::cout << "SetUpTestSuite" << std::endl;
    }

    static void TearDownTestSuite() {
        std::cout << "TearDownTestSuite" << std::endl;
    }

    void SetUp() override { 
        std::cout << "SetUp" << std::endl;

        // Create list with testing_size elements
        for (int i = 0; i < testing_size; ++i) 
            test_list.push_back(i);
    }

    void TearDown() override {
        std::cout << "TearDown" << std::endl;
        test_list.clear();
    }


};


TEST(List, Basic_Test) {
    // Arrange
    const int expectedZeroSize = 0;

    list<int> lst{};

    // Assert
    EXPECT_EQ(lst.size(), expectedZeroSize);

    lst.push_back(1);
    const size_t expectedSize = 1;

    EXPECT_NE(lst.size(), expectedZeroSize);
    EXPECT_EQ(lst.size(), expectedSize);

    EXPECT_LE(lst.size(), expectedSize);
    EXPECT_GE(lst.size(), expectedSize);
}


// 2 test
TEST(List, Copying_Constructor) {
    // Arrange
    list<int> lst{};

    for (int i = 0; i < 10000; i += 1000) {
        lst.push_back(i);
    }

    // Act
    list<int> new_lst = lst;

    // Assert
    EXPECT_EQ(lst.size(), new_lst.size());                        // Equal sizes
    EXPECT_EQ(lst[0], new_lst[0]);
    EXPECT_EQ(lst[lst.size() - 1], new_lst[new_lst.size() - 1]);  // Equal last elements

    lst.push_back(1);

    EXPECT_NE(lst.size(), new_lst.size());                        // Non equal sizes
    EXPECT_NE(lst[lst.size() - 1], new_lst[new_lst.size() - 1]);  // Non equal last element
    EXPECT_GE(lst.size(), new_lst.size());
}


// 3 test
TEST(List, Moving_Constructor) {
    // Arrange
    list<int> lst{};

    for (int i = 0; i < 10000; i += 1000) {
        lst.push_back(i);
    }
    int lst_size = lst.size();
    int last_element = lst[lst.size() - 1];
    int first_element = lst[0];


    // Act
    list<int> new_lst = std::move(lst);

    // Assert
    EXPECT_EQ(new_lst.size(), lst_size);                          // Equal sizes
    EXPECT_EQ(new_lst[0], first_element); 
    EXPECT_EQ(new_lst[new_lst.size() - 1], last_element);         // Equal last elements

    new_lst.push_back(1);

    EXPECT_NE(new_lst.size(), lst_size);                          // Non equal sizes
    EXPECT_NE(new_lst[new_lst.size() - 1], last_element);         // Non equal last element
}


// 4 test
TEST(List, Expected_Sequence_Push_Back) {
    // Arrange
    int expected_sequence[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> lst{};

    for (int i = 0; i < 10; ++i) {
        lst.push_back(i);
    }
    
    // Act
    
    // Assert
    for (int i = 0; i < lst.size(); ++i) {
        EXPECT_EQ(lst[i], expected_sequence[i]);                          // Equal element        
    }    
    
    // erase half of container
    for (int i = 0; i < 5; ++i) {
        lst.erase(0);
    }

    for (int i = 0; i < lst.size(); ++i) {
        EXPECT_EQ(lst[i], expected_sequence[i + 5]);                          // Equal element        
    }


}


// 5 test
TEST(List, Expected_Sequence_Push_Forward) {
    // Arrange
    int expected_sequence[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    list<int> lst{};

    for (int i = 0; i < 10; ++i) {
        lst.insert(i, 0);
    }
    
    // Act
    
    // Assert
    for (int i = 0; i < lst.size(); ++i) {
        EXPECT_EQ(lst[i], expected_sequence[i]);                          // Equal element        
    }

    for (int i = 0; i < 5; ++i) {
        lst.erase(0);
    }

    // erase half of container
    for (int i = 0; i < lst.size(); ++i) {
        EXPECT_EQ(lst[i], expected_sequence[i + 5]);                          // Equal element        
    }
}


// 6 test
TEST(List, Forward_Middle_Back_Insertions) {
    // Arrange
    int expected_sequence[10] = {10, 0, 1, 3, 20, 5, 7, 8, 9, 30};
    const int LEN_IDX = 3; 
    int indexes[LEN_IDX] = {2, 4, 6};

    list<int> lst{};

    for (int i = 0; i < 10; ++i) {
        lst.push_back(i);
    }
    
    // Act
    lst.erase(LEN_IDX, indexes);                                          // Erase 2, 4, 6 - counting from zero
    lst.push_forward(10);
    lst.insert(20, lst.size() / 2);                                       // insert to the middle
    lst.push_back(30);

    // Assert
    for (int i = 0; i < lst.size(); ++i) {
        EXPECT_EQ(lst[i], expected_sequence[i]);                          // Equal element        
    }

    EXPECT_EQ(lst[0], 10);                                                // Equal first element
    EXPECT_EQ(lst[lst.size() / 2 - 1], 20);                               // Equal middle element
    EXPECT_EQ(lst[lst.size() - 1], 30);                                   // Equal last element

}


// 7 test
TEST_F(ListFixture, Inserting_And_Erasing) {
    // Arrange
    int expected_sequence[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int zero_num = 21;
    int last_num = 22;
    int first_num = 23;
    int ten_num = 24;
    
    
    // Act
    test_list.insert(zero_num, 0);
    test_list.insert(last_num, test_list.size() - 1);
    test_list.insert(first_num, 1);
    test_list.insert(ten_num, 10);

    // Assert
    ASSERT_EQ(test_list.size(), 14);
    ASSERT_EQ(test_list[test_list.size() - 1], last_num);
    ASSERT_EQ(test_list[0], zero_num);
    ASSERT_EQ(test_list[1], first_num);
    ASSERT_EQ(test_list[10], ten_num);
    
    // Act again
    test_list.erase(10);                                                      // return list to start state
    test_list.erase(0);
    test_list.erase(0);
    test_list.erase(test_list.size() - 1);

    // Assert again
    ASSERT_EQ(test_list.size(), 10);
    for (int i = 0; i < test_list.size(); ++i) {
        EXPECT_EQ(test_list[i], expected_sequence[i]);                        // Equal element        
    }
}


// 8 test
TEST_F(ListFixture, Erase_All) {
    // Arrange
    // nothing to do here, because we have fixture
    
    // Act
    for (int i = test_list.size() - 1; i >= 0; --i)
        test_list.erase(i);

    // Assert
    ASSERT_EQ(test_list.size(), 0);
}


// 9 test
TEST_F(ListFixture, Push_Back_Forward_Insert) {
    // Arrange
    int back_number = 7;
    int forward_number = 123;
    int insert_number = 1991;
    int insert_placement = 6;
    
    // Act
    test_list.push_back(back_number);
    test_list.push_forward(forward_number);
    test_list.insert(insert_number, insert_placement);

    // Assert
    ASSERT_EQ(test_list[0], forward_number);
    ASSERT_EQ(test_list[test_list.size() - 1], back_number);
    ASSERT_EQ(test_list[insert_placement], insert_number);
    ASSERT_EQ(test_list.size(), 13);
}


// 10 test
TEST_F(ListFixture, Lost_Element_Check) {
    // Arrange

    // Act

    // Assert
    ASSERT_FALSE(test_list[-1]);
    ASSERT_FALSE(test_list[123]);
}

