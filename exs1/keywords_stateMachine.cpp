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
    �����Identifier״̬�������õ��ĵ����ǹؼ��֣���ؼ���״̬�������ɹ�
    @params str ��Identifier״̬�������õ��ĵ���
*/
Result keywords_StateMachine::keywords_recognize(std::string str)
{
    /*Result result;
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
    */

    Result result;

    // �ж�Identifier�����õ��ĵ���
    if (key_words.count(str) > 0)
    {
        // �����õ����ǹؼ���
        result.ID = KEYWORDS_STATEMACHINE;
        result.opt_str = str;
        result.str_len = str.length();
    }
    else
    {
        // ������ǹؼ��֣���һ����Identifier
        result.ID = IDENTIFIER_STATEMACHINE;
        result.opt_str = str;
        result.str_len = str.length();
    }

    return result;
}
