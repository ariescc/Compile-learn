#pragma once

#include "relation.h"
#include "resource.h"

class StateMachine {
public:
	// ������ĸ�����ַ�������
	std::string lower_letter_list = "abcdefghijklmnopqrstuvwxyz";
	std::string upper_letter_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string number_list = "0123456789";

	std::map<Relation, int> mp; // �洢ӳ���ϵ
	std::vector<Relation> relations; // �洢�ɺϷ�ת����״̬
	std::map<int, bool> isAccept; // �Ƿ�Ϊ����״̬

	StateMachine();
};