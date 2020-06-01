//
// Created by liulizhang on 2020/5/25.
//

#ifndef REVERSE_SOURCEMAP_INCLUDE_SOURCEMAP_VAL_H_
#define REVERSE_SOURCEMAP_INCLUDE_SOURCEMAP_VAL_H_
struct sourceMap_Val {
  int beforeRow;
  int beforeColumn;
  int afterRow;
  int afterColumn;
  int sourcesVal;
  int namesVal;
  void init(){
    beforeRow=beforeColumn=afterRow=afterColumn=sourcesVal=namesVal=0;
  }
};

#endif //REVERSE_SOURCEMAP_INCLUDE_SOURCEMAP_VAL_H_
