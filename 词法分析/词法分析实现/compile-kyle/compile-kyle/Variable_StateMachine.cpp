#include "Variable_StateMachine.h"

// ���캯��
Variable_StateMachine::Variable_StateMachine() {}

// ��ʼ��������ֵ״̬��
void Variable_StateMachine::init() {
	
	// ��ʼ����״̬�Ƿ�Ϊ����״̬
	isAccept[1] = false;
	isAccept[2] = false;
	isAccept[3] = true;

	// �����е���ĸ����״̬1or2��ӳ��
	// ������0-9���ִ���״̬Ϊ2��ӳ��
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


	// ��ĸ�����ֶ�Ŀ��״̬2����ӳ��
	for (int i = 0; i < relations.size(); i++) {
		// cout << i << " " << relations[i].state << " " << relations[i].ch << endl;
		mp[relations[i]] = 2;
	}

}

// ״̬����������ID�������ַ���
Result Variable_StateMachine::variable_recognize(std::string str) {
	int state = 1;
	int i = 0;
	std::string res = "failed!!!";
	char curCh = str[i];

	// ��ǰ״̬���ǽ���״̬ʱ����ִ��ѭ�� falseʱ��ִ��
	while (!isAccept[state] && i < str.length()) {

		//std::cout << "state: " << state << std::endl;

		Relation relation;
		relation.state = state;
		relation.ch = curCh;

		//std::cout << "test case: " << relation.state << " " << relation.ch << std::endl;

		state = mp[relation];
		// �Ƿ�ӳ��
		if (!state) {
			state = 3;
			break;
		}
		curCh = str[++i];
	}

	res = str.substr(0, i);

	Result output;

	// δ��ȡ���Ϸ����ַ���
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
