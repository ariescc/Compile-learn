#pragma once

#include "relation.h"
#include "resource.h"

class StateMachine {
public:
	// 定义字母数字字符串常量
	std::string lower_letter_list = "abcdefghijklmnopqrstuvwxyz";
	std::string upper_letter_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string number_list = "0123456789";

	std::map<Relation, int> mp; // 存储映射关系
	std::vector<Relation> relations; // 存储可合法转换的状态
	std::map<int, bool> isAccept; // 是否为接受状态

	StateMachine();
};