#pragma once

#include "StateMachine.h"

// 变量赋值状态机
class Variable_StateMachine : public StateMachine {
public:
	Variable_StateMachine();
	void init(); // 初始化状态机
	Result variable_recognize(std::string str); // 解析输入字符串
};
