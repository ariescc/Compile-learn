/**
    定义词法分析的结果
*/

#pragma once

#include <string>

class WordAnalyse_Result {
public:
    int line = 1; // 分析得到的单词所处的代码行数，默认为1。只用于打印词法分析结果中使用
	int ID;
	std::string opt_str;
	int str_len; // 解析出来的字符串的长度

	WordAnalyse_Result();
};




