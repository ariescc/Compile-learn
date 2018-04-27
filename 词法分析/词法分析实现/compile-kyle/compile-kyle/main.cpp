#include "Variable_StateMachine.h"

// ������ֵ״̬��
Variable_StateMachine variable_statemachine; 

void initialize() {
	variable_statemachine.init();
}

int main()
{
	std::string input;
	std::cin >> input;

	initialize();

	Result variable_opt = variable_statemachine.variable_recognize(input);

	//std::cout << "ID: " << variable_opt.ID << " String Output: " << variable_opt.opt_str << std::endl;
	std::cout << "ID: " << variable_opt.ID << std::endl;
	std::cout << "String output: " << variable_opt.opt_str << std::endl;

	system("pause");
	return 0;
}