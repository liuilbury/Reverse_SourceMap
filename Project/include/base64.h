//
// Created by liulizhang on 2020/5/22.
//

#ifndef REVERSE_SOURCEMAP_INCLUDE_BASE64_H_
#define REVERSE_SOURCEMAP_INCLUDE_BASE64_H_
#include <string>
#include <stdexcept>
class base64 {
 public:
  const std::string base64Map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  char intToChar(int number);
  int charToInt(char charCode);
};

#endif //REVERSE_SOURCEMAP_INCLUDE_BASE64_H_
