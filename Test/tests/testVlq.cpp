//
// Created by liulizhang on 2020/5/28.
//
#include "gtest/gtest.h"
#include "vlq.h"

class testVlq : public ::testing::Test{
 public:
  vlq test;
};

TEST_F(testVlq, vlq_true) {
  std::vector<int>res;
  EXPECT_EQ(test.revCode("a"),std::vector<int>{13});
  EXPECT_EQ(test.revCode("c"),std::vector<int>{14});
  EXPECT_EQ(test.revCode("e"),std::vector<int>{15});
  EXPECT_EQ(test.revCode("yB"),std::vector<int>{25});
  EXPECT_EQ(test.revCode("gC"),std::vector<int>{32});
  EXPECT_EQ(test.revCode("kD"),std::vector<int>{50});
  EXPECT_EQ(test.revCode("gkxH"),std::vector<int>{123456});
  EXPECT_EQ(test.revCode("ace"),(std::vector<int>{13,14,15}));
}
TEST_F(testVlq,vlq_false_Len){
  EXPECT_THROW(test.revCode("k"),std::domain_error);

}
TEST_F(testVlq,vlq_false_base64){
  EXPECT_THROW(test.revCode("k@"),std::domain_error);
}