#pragma once

#include "StateMachine.h"

// ������ֵ״̬��
class Variable_StateMachine : public StateMachine {
public:
	Variable_StateMachine();
	void init(); // ��ʼ��״̬��
	Result variable_recognize(std::string str); // ���������ַ���
};
