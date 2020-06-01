//
// Created by liulizhang on 2020/5/22.
//

#include "../include/vlq.h"
int VLQ_BASE_SHIFT = 5;

// binary: 100000
int VLQ_BASE = 1 << VLQ_BASE_SHIFT;

// binary: 011111
int VLQ_BASE_MASK = VLQ_BASE - 1;

// binary: 100000
int VLQ_CONTINUATION_BIT = VLQ_BASE;
int vlq::setVlqSigned(int value) {
  return value<0?((-value)<<1)+1:(value<<1);
}
bool vlq::getVlqSigned(int value) {
  return (value&1)?(value>>1):-(value>>1);
}
std::string vlq::getCode() {
	return "";
}
std::vector<int> vlq::revCode(std::string vStr) {
  std::vector<int>ans;
  int result=0;
  int shift=0;
  bool continuation=0;
  for(int i=0;i<vStr.size();i++){
	int digit=base64().charToInt(vStr[i]);
	if(digit==-1)throw "Invalid base64 digit"+vStr[i];
	continuation=digit&VLQ_CONTINUATION_BIT;
	digit&=VLQ_BASE_MASK;
	result+=digit<<shift;
	if(continuation){
	  shift+=VLQ_BASE_SHIFT;
	}else {
	  bool isNegate=result&1;
	  result>>=1;
	  ans.push_back(isNegate?-result:result);
	  result=shift=0;
	}
  }
  if(continuation)throw "Expected more digits in base 64 VLQ value.";
  return ans;
}