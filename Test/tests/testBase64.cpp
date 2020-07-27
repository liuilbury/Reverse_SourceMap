//
// Created by liulizhang on 2020/5/28.
//

#include "gtest/gtest.h"
#include "base64.h"
class test_base64 : public ::testing::Test {
 public:
  const std::string base64Map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  base64 test;
};

TEST_F(test_base64, char_true) {
  for(int i=0;i<64;i++){
	EXPECT_EQ(test.intToChar(i),base64Map[i]);
  }
}

TEST_F(test_base64, int_true) {
  for(int i=0;i<64;i++){
    EXPECT_EQ(test.charToInt(base64Map[i]),i);
  }
}

TEST_F(test_base64, char_false) {
  EXPECT_EQ(test.charToInt('@'),-1);
  EXPECT_EQ(test.charToInt(' '),-1);
  EXPECT_EQ(test.charToInt('$'),-1);
  EXPECT_EQ(test.charToInt('%'),-1);
}

TEST_F(test_base64,int_false){
  EXPECT_THROW(test.intToChar(-1),std::domain_error);
  EXPECT_THROW(test.intToChar(64),std::domain_error);
  EXPECT_THROW(test.intToChar(1000),std::domain_error);
}