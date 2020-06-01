//
// Created by liulizhang on 2020/5/22.
//

#ifndef REVERSE_SOURCEMAP_INCLUDE_REV_SOURCEMAP_H_
#define REVERSE_SOURCEMAP_INCLUDE_REV_SOURCEMAP_H_
#include "vlq.h"
#include "sourceMap_Val.h"
#include <fstream>
struct Res{
  int row,col;
  std::string sources;
  std::string to_string(){
    return std::to_string(row)+' '+std::to_string(col)+' '+sources;
  }
};
class rev_SourceMap : public vlq {
 public:
  void run(std::string);
  std::vector<Res>rev_SourceMap::findAll(std::vector<std::pair<int,int>>);
  Res find(int row, int col);
 private:
  sourceMap_Val now;
  std::vector<std::string> file;
  std::vector<std::string> sources;
  std::vector<std::string> names;
  std::vector<std::string> mappings;
  std::vector<sourceMap_Val> val;
  void init(std::string sourceMap);
  std::vector<std::string> handleMappings(std::string mapping);
};
#endif //REVERSE_SOURCEMAP_INCLUDE_REV_SOURCEMAP_H_
