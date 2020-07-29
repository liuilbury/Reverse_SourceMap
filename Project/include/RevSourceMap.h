//
// Created by liulizhang on 2020/5/22.
//

#ifndef REVERSE_SOURCEMAP_INCLUDE_REV_SOURCEMAP_H_
#define REVERSE_SOURCEMAP_INCLUDE_REV_SOURCEMAP_H_
#include <vector>
#include <fstream>
struct sourceMap_Val
{
	int beforeRow;
	int beforeColumn;
	int afterRow;
	int afterColumn;
	int sourcesVal;
	int namesVal;
	void init()
	{
		beforeRow = beforeColumn = afterRow = afterColumn = sourcesVal = namesVal = 0;
	}
};
struct Res
{
	int row, col;
	std::string sources;
	std::string to_string()
	{
		return std::to_string(row) + ' ' + std::to_string(col) + ' ' + sources;
	}
};
class RevSourceMap
{
 private:
	sourceMap_Val m_nowPos;
	std::vector<std::string> m_files;
	std::vector<std::string> m_sources;
	std::vector<std::string> m_names;
	std::vector<std::string> m_mappings;
	std::vector<sourceMap_Val> m_res;
	std::vector<std::string> handleMappings(std::string mapping);
	void init(std::string sourceMap);
	int base64CharToInt(char charCode);
	std::vector<int> vlqRevCode(std::string vStr);
 public:
	void runString(std::string);
	void runFile(std::string);
	Res find(int row, int col);
	std::vector<Res> findAll(std::vector<std::pair<int, int>>qry);
};
#endif //REVERSE_SOURCEMAP_INCLUDE_REV_SOURCEMAP_H_
