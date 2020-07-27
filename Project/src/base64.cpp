//
// Created by liulizhang on 2020/5/22.
//

#include "../include/base64.h"
char base64::intToChar(int number) {
  if (0 <= number && number <= 63) {
	return base64Map[number];
  }
  throw std::domain_error("Must be between 0 and 63: " + number);
}
int base64::charToInt(char charCode) {
  // 0 - 25: ABCDEFGHIJKLMNOPQRSTUVWXYZ
  if ('A' <= charCode && charCode <= 'Z') {
	return charCode - 'A';
  }
  // 26 - 51: abcdefghijklmnopqrstuvwxyz
  if ('a' <= charCode && charCode <= 'z') {
	return charCode - 'a' + 26;
  }
  // 52 - 61: 0123456789
  if ('0' <= charCode && charCode <= '9') {
	return charCode - '0' + 52;
  }
  // 62: +
  if (charCode == '+') {
	return 62;
  }
  // 63: /
  if (charCode == '/') {
	return 63;
  }
  return -1;
}