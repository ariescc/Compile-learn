/**
    ����ʷ������Ľ��
*/

#pragma once

#include <string>

class WordAnalyse_Result {
public:
    int line = 1; // �����õ��ĵ��������Ĵ���������Ĭ��Ϊ1��ֻ���ڴ�ӡ�ʷ����������ʹ��
	int ID;
	std::string opt_str;
	int str_len; // �����������ַ����ĳ���

	WordAnalyse_Result();
};




