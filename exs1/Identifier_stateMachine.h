#include "StateMachine.h"

class Identifier_StateMachine : public StateMachine {
public:
	Identifier_StateMachine();
	void init();
	Result identifier_recognize(std::string str);
};

