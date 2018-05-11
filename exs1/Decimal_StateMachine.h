#include "StateMachine.h"

class Decimal_StateMachine : public StateMachine {
public:
	Decimal_StateMachine();
	void init();
	Result decimal_recognize(std::string str);
};

