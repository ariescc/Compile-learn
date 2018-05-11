#include "StateMachine.h"

class keywords_StateMachine : public StateMachine {
public:

    std::set<std::string> key_words = {"thread",  "features",  "flows",  "properties",  "end",
     "none",  "in",  "out",  "data",  "port",  "event",  "parameter",  "flow" ,  "source",
     "sink" ,  "path",  "constant" ,  "access"};

	keywords_StateMachine();
	void init();
	Result keywords_recognize(std::string str);
};

