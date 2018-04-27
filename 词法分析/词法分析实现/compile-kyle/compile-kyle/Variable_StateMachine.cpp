#include "Variable_StateMachine.h"

// 构造函数
Variable_StateMachine::Variable_StateMachine() {}

// 初始化变量赋值状态机
void Variable_StateMachine::init() {
	
	// 初始化各状态是否为接受状态
	isAccept[1] = false;
	isAccept[2] = false;
	isAccept[3] = true;

	// 对所有的字母创建状态1or2的映射
	// 对所有0-9数字创建状态为2的映射
	for (int i = 0; i < LETTER_NUM; i++) {
		Relation relation1, relation2, relation3, relation4;

		relation1.state = 1;
		relation1.ch = upper_letter_list[i];

		relation2.state = 1;
		relation2.ch = lower_letter_list[i];

		relation3.state = 2;
		relation3.ch = upper_letter_list[i];

		relation4.state = 2;
		relation4.ch = lower_letter_list[i];

		relations.push_back(relation1);
		relations.push_back(relation2);
		relations.push_back(relation3);
		relations.push_back(relation4);
	}

	for (int i = 0; i < DIGIT_NUM; i++) {
		Relation relation;

		relation.state = 2;
		relation.ch = number_list[i];

		relations.push_back(relation);
	}


	// 字母和数字对目标状态2进行映射
	for (int i = 0; i < relations.size(); i++) {
		// cout << i << " " << relations[i].state << " " << relations[i].ch << endl;
		mp[relations[i]] = 2;
	}

}

// 状态机解析返回ID及解析字符串
Result Variable_StateMachine::variable_recognize(std::string str) {
	int state = 1;
	int i = 0;
	std::string res = "failed!!!";
	char curCh = str[i];

	// 当前状态不是接受状态时可以执行循环 false时可执行
	while (!isAccept[state] && i < str.length()) {

		//std::cout << "state: " << state << std::endl;

		Relation relation;
		relation.state = state;
		relation.ch = curCh;

		//std::cout << "test case: " << relation.state << " " << relation.ch << std::endl;

		state = mp[relation];
		// 非法映射
		if (!state) {
			state = 3;
			break;
		}
		curCh = str[++i];
	}

	res = str.substr(0, i);

	Result output;

	// 未截取到合法的字符串
	if (!i) {
		output.ID = -1;
		output.opt_str = "Illegal string!";
	}
	else {
		output.ID = VARIABLE_STATEMACHINE;
		output.opt_str = res;
	}

	return output;
	//std::cout << "String output: " << res << std::endl;
}
