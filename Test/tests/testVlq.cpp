//
// Created by liulizhang on 2020/5/28.
//
#include "gtest/gtest.h"
#define private public
#include "RevSourceMap.h"
#undef private

class testVlq : public ::testing::Test{
 public:
	RevSourceMap test;
};

TEST_F(testVlq, vlq_true) {
  std::vector<int>res;
  EXPECT_EQ(test.vlqRevCode("a"),std::vector<int>{13});
  EXPECT_EQ(test.vlqRevCode("c"),std::vector<int>{14});
  EXPECT_EQ(test.vlqRevCode("e"),std::vector<int>{15});
  EXPECT_EQ(test.vlqRevCode("yB"),std::vector<int>{25});
  EXPECT_EQ(test.vlqRevCode("gC"),std::vector<int>{32});
  EXPECT_EQ(test.vlqRevCode("kD"),std::vector<int>{50});
  EXPECT_EQ(test.vlqRevCode("gkxH"),std::vector<int>{123456});
  EXPECT_EQ(test.vlqRevCode("ace"),(std::vector<int>{13,14,15}));
}
TEST_F(testVlq,vlq_false_Len){
  EXPECT_THROW(test.vlqRevCode("k"),std::domain_error);

}
TEST_F(testVlq,vlq_false_base64){
  EXPECT_THROW(test.vlqRevCode("k@"),std::domain_error);
}