//
// Created by liulizhang on 2020/5/22.
//

#include "RevSourceMap.h"
int RevSourceMap::base64CharToInt(char charCode)
{
	// 0 - 25: ABCDEFGHIJKLMNOPQRSTUVWXYZ
	if ('A' <= charCode && charCode <= 'Z')
	{
		return charCode - 'A';
	}
	// 26 - 51: abcdefghijklmnopqrstuvwxyz
	if ('a' <= charCode && charCode <= 'z')
	{
		return charCode - 'a' + 26;
	}
	// 52 - 61: 0123456789
	if ('0' <= charCode && charCode <= '9')
	{
		return charCode - '0' + 52;
	}
	// 62: +
	if (charCode == '+')
	{
		return 62;
	}
	// 63: /
	if (charCode == '/')
	{
		return 63;
	}
	return -1;
}

std::vector<int> RevSourceMap::vlqRevCode(std::string vStr)
{
	int VLQ_BASE_SHIFT = 5;
// binary: 100000
	int VLQ_BASE = 1 << VLQ_BASE_SHIFT;
// binary: 011111
	int VLQ_BASE_MASK = VLQ_BASE - 1;
// binary: 100000
	int VLQ_CONTINUATION_BIT = VLQ_BASE;
	std::vector<int> ans;
	int result = 0;
	int shift = 0;
	bool continuation = 0;
	for (int i = 0; i < vStr.size(); i++)
	{
		int digit = base64CharToInt(vStr[i]);
		if (digit == -1)throw std::domain_error("Invalid base64 digit " + vStr[i]);
		continuation = digit & VLQ_CONTINUATION_BIT;
		digit &= VLQ_BASE_MASK;
		result += digit << shift;
		if (continuation)
		{
			shift += VLQ_BASE_SHIFT;
		}
		else
		{
			bool isNegate = result & 1;
			result >>= 1;
			ans.push_back(isNegate ? -result : result);
			result = shift = 0;
		}
	}
	if (continuation)throw std::domain_error("Expected more digits in base 64 VLQ value.");
	return ans;
}
void RevSourceMap::init(std::string sourceMap)
{
	m_nowPos.init();
	m_files.clear();
	m_sources.clear();
	m_names.clear();
	m_mappings.clear();
	m_res.clear();
	int cnt = 0;
	std::vector<std::string> v;
	std::string s;
	for (int i = 0; i < sourceMap.size(); i++)
	{
		///解析json文件
		if (sourceMap[i] == '\\')
		{
			i++;
			s += sourceMap[i];
			continue;
		}
		if (sourceMap[i] == '"')
		{
			cnt++;
		}
		if (cnt == 2)
		{
			v.push_back(s);
			s = "";
			cnt = 0;
		}
		else if (cnt == 1)
		{
			if (sourceMap[i] != '"')
				s += sourceMap[i];
		}
	}
	std::string mark = "";
	for (auto i:v)
	{
		if (i == "sources" || i == "names" || i == "mappings" || i == "file" || i == "sourcesContent"
			|| i == "sourceRoot")
		{
			mark = i;
		}
		else if (mark == "sources")
		{
			m_sources.push_back(i);
		}
		else if (mark == "names")
		{
			m_names.push_back(i);
		}
		else if (mark == "mappings")
		{
			m_mappings.push_back(i);
		}
		else if (mark == "file")
		{
			m_files.push_back(i);
		}
		else if (mark == "sourcesContent")
		{

		}
		else if (mark == "sourceRoot")
		{

		}
	}
	m_mappings = handleMappings(m_mappings[0]);
//    	- 第一位，表示这个位置在（转换后的代码的）的第几列。
//
//		- 第二位，表示这个位置属于sources属性中的哪一个文件。
//
//　　	- 第三位，表示这个位置属于转换前代码的第几行。
//
//　　	- 第四位，表示这个位置属于转换前代码的第几列。
//
//　　	- 第五位，表示这个位置属于names属性中的哪一个变量。
#ifdef SM_DEBUG
	std::ofstream outfile;
	outfile.open("../2");
#endif
	for (auto i:m_mappings)
	{
		if (i == ";")
		{
			m_nowPos.afterRow++, m_nowPos.afterColumn = 0;
			continue;
		}
		std::vector<int> ans = vlqRevCode(i);
		if (ans.size() == 1)
		{
			m_nowPos.afterColumn += ans[0];
			continue;
		}
		m_nowPos.afterColumn += ans[0];
		m_nowPos.sourcesVal += ans[1];
		m_nowPos.beforeRow += ans[2];
		m_nowPos.beforeColumn += ans[3];
		if (ans.size() == 5)
		{
			m_nowPos.namesVal += ans[4];
		}
		m_res.push_back({ m_nowPos.beforeRow, m_nowPos.beforeColumn, m_nowPos.afterRow, m_nowPos.afterColumn, m_nowPos.sourcesVal, m_nowPos.namesVal });

#ifdef SM_DEBUG
		outfile << i<<" "<<m_nowPos.beforeRow << " " << m_nowPos.beforeColumn << " " << m_nowPos.afterRow << " " << m_nowPos.afterColumn << " "
				  << m_sources[m_nowPos.sourcesVal] <<" " <<std::endl;
#endif
	}
	m_mappings.clear();
	m_mappings.shrink_to_fit();
	v.clear();
	v.shrink_to_fit();
}
std::vector<std::string> RevSourceMap::handleMappings(std::string mapping)
{
	std::vector<std::string> res;
	std::string s;
	for (int i = 0; i < mapping.size(); i++)
	{
		if (mapping[i] == ',')
		{
			res.push_back(s);
			s = "";
		}
		else if (mapping[i] == ';')
		{
			if (s != "")
				res.push_back(s);
			s = "";
			res.push_back(";");
		}
		else
		{
			s += mapping[i];
		}
	}
	if (s != "")
	{
		res.push_back(s);
	}
	return res;
}
void RevSourceMap::runFile(std::string mapPath)
{
	std::string s;
	std::ifstream infile;
	infile.open(mapPath);
	std::getline(infile, s);
	init(s);
	infile.close();
}
void RevSourceMap::runString(std::string mapString)
{
	init(mapString);
}

Res RevSourceMap::find(int row, int col)
{
	row--;
	col--;
	Res ans;
	int l = 0, r = m_res.size() - 1, res = 0;
	if (row > m_res[m_res.size() - 1].afterRow)
	{
		return Res{ row + 1, col + 1, m_files[0] };
	}
	while (r - l >= 0)
	{
		int mid = (r + l) / 2;
		if (m_res[mid].afterRow == row && m_res[mid].afterColumn > col || m_res[mid].afterRow > row)
		{
			r = mid - 1;
		}
		else
		{
			res = mid;
			l = mid + 1;
		}
	}
	return Res{ m_res[res].beforeRow + 1, m_res[res].beforeColumn + 1, m_sources[m_res[res].sourcesVal] };
}
std::vector<Res> RevSourceMap::findAll(std::vector<std::pair<int, int>> qry)
{
	int row, col;
	std::vector<Res> ans;
	for (auto q:qry)
	{
		row = q.first;
		col = q.second;
		ans.push_back(find(row, col));
	}
	return ans;
}
