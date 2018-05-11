#pragma once

#include "relation.h"
#include "resource.h"

class StateMachine {
public:

	std::string lower_letter_list = "abcdefghijklmnopqrstuvwxyz";
	std::string upper_letter_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string number_list = "0123456789";

	std::map<Relation, int> mp; // 状态映射关系
	std::vector<Relation> relations;
	std::map<int, bool> isAccept; // 状态结点是否为接受状态

	StateMachine();
};
