#include "StateMachine.h"

class symbols_StateMachine : public StateMachine {
public:

    // "=>", "+=>", ";", ":", "::", "{", "}", "->"

    // 如果符号的长度为1，则通过set进行索引。
//    std::set<std::string> symbols = {";", ":", "{", "}"};

    // 如果符号的长度大于1，则为此符号创建一个状态机

    /*
    ===========================================================================================
    =>
    ===========================================================================================
    */
    std::map<int, bool> isAccept1;
    std::map<Relation, int> sym1;

    /*
    ===========================================================================================
    +=>
    ===========================================================================================
    */
    std::map<int, bool> isAccept2;
    std::map<Relation, int> sym2;


    /*
    ===========================================================================================
    ::
    ===========================================================================================
    */
    std::map<int, bool> isAccept3;
    std::map<Relation, int> sym3;



    /*
    ===========================================================================================
    ->
    ===========================================================================================
    */
    std::map<int, bool> isAccept4;
    std::map<Relation, int> sym4;

    /*
    ===========================================================================================
    :
    ===========================================================================================
    */
    std::map<int, bool> isAccept5;
    std::map<Relation, int> sym5;

    /*
    ===========================================================================================
    ;
    ===========================================================================================
    */
    std::map<int, bool> isAccept6;
    std::map<Relation, int> sym6;

    /*
    ===========================================================================================
    {
    ===========================================================================================
    */
    std::map<int, bool> isAccept7;
    std::map<Relation, int> sym7;

    /*
    ===========================================================================================
    }
    ===========================================================================================
    */
    std::map<int, bool> isAccept8;
    std::map<Relation, int> sym8;

	symbols_StateMachine();
	void init();
	// 运行所有符号状态机解析，并且使用符号集合映射解析
	WordAnalyse_Result symbols_recognize(std::string str);

	// 状态机解析（封装公用函数）
	WordAnalyse_Result public_recognize(std::map<int, bool>& isaccept, std::map<Relation, int>& mmp, std::string str);

	// 符号集合解析
	WordAnalyse_Result symbols_recognize_set(std::string str);
};


