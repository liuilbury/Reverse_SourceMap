//
// Created by liulizhang on 2020/5/22.
//

#include "../include/rev_SourceMap.h"
#include <iostream>
void rev_SourceMap::init(std::string sourceMap) {
  now.init();
  file.clear();
  sources.clear();
  names.clear();
  mappings.clear();
  val.clear();
  int cnt = 0;
  std::vector<std::string> v;
  std::string s;
  for (int i = 0; i < sourceMap.size(); i++) {
	///解析json文件
	if(sourceMap[i]=='\\'){
	  i++;
	  s+=sourceMap[i];
	  continue;
	}
	if (sourceMap[i] == '"') {
	  cnt++;
	}
	if (cnt == 2) {
	  v.push_back(s);
	  s = "";
	  cnt = 0;
	} else if (cnt == 1) {
	  if (sourceMap[i] != '"')
		s += sourceMap[i];
	}
  }
  std::string mark = "";
  for (auto i:v) {
	if (i == "sources" || i == "names" || i == "mappings" || i == "file" || i == "sourcesContent"
		|| i == "sourceRoot") {
	  mark = i;
	} else if (mark == "sources") {
	  sources.push_back(i);
	} else if (mark == "names") {
	  names.push_back(i);
	} else if (mark == "mappings") {
	  mappings.push_back(i);
	} else if (mark == "file") {
	  file.push_back(i);
	} else if (mark == "sourcesContent") {

	} else if (mark == "sourceRoot") {

	}
  }
  mappings = handleMappings(mappings[0]);
//    	- 第一位，表示这个位置在（转换后的代码的）的第几列。
//
//		- 第二位，表示这个位置属于sources属性中的哪一个文件。
//
//　　	- 第三位，表示这个位置属于转换前代码的第几行。
//
//　　	- 第四位，表示这个位置属于转换前代码的第几列。
//
//　　	- 第五位，表示这个位置属于names属性中的哪一个变量。
#ifdef DEBUG
  std::ofstream outfile;
  outfile.open("C:\\Users\\liulizhang\\CLionProjects\\Reverse-SourceMap\\Test\\tests\\testMap\\2");
#endif
  for (auto i:mappings) {
	if (i == ";") {
	  now.afterRow++, now.afterColumn = 0;
	  continue;
	}
	std::vector<int> ans = vlq().revCode(i);
	if (ans.size() == 1) {
	  now.afterColumn += ans[0];
	  continue;
	}
	now.afterColumn += ans[0];
	now.sourcesVal += ans[1];
	now.beforeRow += ans[2];
	now.beforeColumn += ans[3];
	if (ans.size() == 5) {
	  now.namesVal += ans[4];
	}
	val.push_back({now.beforeRow, now.beforeColumn, now.afterRow, now.afterColumn, now.sourcesVal, now.namesVal});

#ifdef DEBUG
	outfile << i<<" "<<now.beforeRow << " " << now.beforeColumn << " " << now.afterRow << " " << now.afterColumn << " "
			  << sources[now.sourcesVal] <<" " <<std::endl;
#endif
  }
  mappings.clear();
  mappings.shrink_to_fit();
  v.clear();
  v.shrink_to_fit();
}
std::vector<std::string> rev_SourceMap::handleMappings(std::string mapping) {
  std::vector<std::string> res;
  std::string s;
  for (int i = 0; i < mapping.size(); i++) {
	if (mapping[i] == ',') {
	  res.push_back(s);
	  s = "";
	} else if (mapping[i] == ';') {
	  if (s != "")
		res.push_back(s);
	  s = "";
	  res.push_back(";");
	} else {
	  s += mapping[i];
	}
  }
  if(s!=""){
    res.push_back(s);
  }
  return res;
}
void rev_SourceMap::runFile(std::string mapPath) {
  std::string s;
  std::ifstream infile;
  infile.open(mapPath);
  std::getline(infile, s);
  init(s);
  infile.close();
}
void rev_SourceMap::runString(std::string mapString) {
	init(mapString);
}

Res rev_SourceMap::find(int row, int col) {
  row--;
  col--;
  Res ans;
  int l = 0, r = val.size() - 1, res = 0;
  if (row > val[val.size() - 1].afterRow) {
	return Res{row+1, col+1, file[0]};
  }
  while (r - l >= 0) {
	int mid = (r + l) / 2;
	if (val[mid].afterRow == row && val[mid].afterColumn > col || val[mid].afterRow > row) {
	  r = mid - 1;
	} else {
	  res = mid;
	  l = mid + 1;
	}
  }
  return Res{val[res].beforeRow + 1, val[res].beforeColumn + 1, sources[val[res].sourcesVal]};
}
std::vector<Res>rev_SourceMap::findAll(std::vector<std::pair<int,int>>query){
  int row,col;
  std::vector<Res>ans;
  for(auto q:query){
    row=q.first;
    col=q.second;
    ans.push_back(find(row,col));
  }
  return ans;
}