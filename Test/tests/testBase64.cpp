//
// Created by liulizhang on 2020/5/28.
//

#include "gtest/gtest.h"
#define private public
#include "RevSourceMap.h"
#undef private
class test_base64 : public ::testing::Test {
 public:
  const std::string base64Map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  RevSourceMap test;
};


TEST_F(test_base64, char_true) {
  for(int i=0;i<64;i++){
    EXPECT_EQ(test.base64CharToInt(base64Map[i]),i);
  }
}

TEST_F(test_base64, char_false) {
  EXPECT_EQ(test.base64CharToInt('@'),-1);
  EXPECT_EQ(test.base64CharToInt(' '),-1);
  EXPECT_EQ(test.base64CharToInt('$'),-1);
  EXPECT_EQ(test.base64CharToInt('%'),-1);
}