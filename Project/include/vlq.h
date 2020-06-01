//
// Created by liulizhang on 2020/5/22.
//

#ifndef REVERSE_SOURCEMAP_INCLUDE_VLQ_H
#define REVERSE_SOURCEMAP_INCLUDE_VLQ_H
#include "base64.h"
#include <vector>
class vlq : public base64 {
 public:
  std::vector<int> revCode(std::string vStr);
 private:
  bool getVlqSigned(int value);
  int setVlqSigned(int value);
  std::string getCode();
};

#endif //REVERSE_SOURCEMAP_INCLUDE_VLQ_H
