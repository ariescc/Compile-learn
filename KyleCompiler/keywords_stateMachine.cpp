#include "keywords_stateMachine.h"

keywords_StateMachine::keywords_StateMachine() {}

/**
    �ؼ���״̬����ʼ��
*/
void keywords_StateMachine::init()
{
    kwd_mp["thread"] = THREAD;
    kwd_mp["features"] = FEATURES;
    kwd_mp["flows"] = FLOWS;
    kwd_mp["properties"] = PROPERTIES;
    kwd_mp["end"] = END;
    kwd_mp["none"] = NONE;
    kwd_mp["in"] = IN;
    kwd_mp["out"] = OUT;
    kwd_mp["data"] = DATA;
    kwd_mp["port"] = PORT;
    kwd_mp["event"] = EVENT;
    kwd_mp["parameter"] = PARAMETER;
    kwd_mp["flow"] = FLOW;
    kwd_mp["source"] = SOURCE;
    kwd_mp["sink"] = SINK;
    kwd_mp["path"] = PATH;
    kwd_mp["constant"] = CONSTANT;
    kwd_mp["access"] = ACCESS;
}

/**
    �ؼ��ֽ���
    �����Identifier״̬�������õ��ĵ����ǹؼ��֣���ؼ���״̬�������ɹ�
    @params str ��Identifier״̬�������õ��ĵ���
*/
WordAnalyse_Result keywords_StateMachine::keywords_recognize(std::string str)
{
    /*WordAnalyse_Result WordAnalyse_Result;
    if (key_words.count(str) > 0)
    {
        WordAnalyse_Result.str_len = str.length();
        WordAnalyse_Result.ID = 1004;
        WordAnalyse_Result.opt_str = str;
    }
    else
    {
        WordAnalyse_Result.str_len = -1;
        WordAnalyse_Result.ID = -1;
        WordAnalyse_Result.opt_str = "Illegal string!";
    }
    return WordAnalyse_Result;
    */

    WordAnalyse_Result WordAnalyse_Result;

    // �ж�Identifier�����õ��ĵ���
    if (key_words.count(str) > 0)
    {

        // �����õ����ǹؼ���
        WordAnalyse_Result.ID = kwd_mp[str];
        WordAnalyse_Result.opt_str = str;
        WordAnalyse_Result.str_len = str.length();
    }
    else
    {
        // ������ǹؼ��֣���һ����Identifier
        WordAnalyse_Result.ID = IDENTIFIER_STATEMACHINE;
        WordAnalyse_Result.opt_str = str;
        WordAnalyse_Result.str_len = str.length();
    }

    return WordAnalyse_Result;
}

