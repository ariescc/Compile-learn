#include "keywords_stateMachine.h"

keywords_StateMachine::keywords_StateMachine() {}

/**
    �ؼ���״̬����ʼ��
*/
void keywords_StateMachine::init()
{
}

/**
    �ؼ��ֽ���
*/
Result keywords_StateMachine::keywords_recognize(std::string str)
{
    Result result;
    if (key_words.count(str) > 0)
    {
        result.str_len = str.length();
        result.ID = 1004;
        result.opt_str = str;
    }
    else
    {
        result.str_len = -1;
        result.ID = -1;
        result.opt_str = "Illegal string!";
    }
    return result;
}
