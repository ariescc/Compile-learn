#include "StateMachine.h"

class keywords_StateMachine : public StateMachine {
public:

    // ¹Ø¼ü×Ö¼¯ºÏ
    std::set<std::string> key_words = {"thread",  "features",  "flows",  "properties",  "end",
     "none",  "in",  "out",  "data",  "port",  "event",  "parameter",  "flow" ,  "source",
     "sink" ,  "path",  "constant" ,  "access"};

    std::map<std::string, int> kwd_mp;

	keywords_StateMachine();
	void init();
	WordAnalyse_Result keywords_recognize(std::string str);
};


