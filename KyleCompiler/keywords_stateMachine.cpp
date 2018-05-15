#include "keywords_stateMachine.h"

keywords_StateMachine::keywords_StateMachine() {}

/**
    关键字状态机初始化
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
    关键字解析
    如果经Identifier状态机解析得到的单词是关键字，则关键字状态机解析成功
    @params str 经Identifier状态机解析得到的单词
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

    // 判断Identifier解析得到的单词
    if (key_words.count(str) > 0)
    {

        // 解析得到的是关键字
        WordAnalyse_Result.ID = kwd_mp[str];
        WordAnalyse_Result.opt_str = str;
        WordAnalyse_Result.str_len = str.length();
    }
    else
    {
        // 如果不是关键字，就一定是Identifier
        WordAnalyse_Result.ID = IDENTIFIER_STATEMACHINE;
        WordAnalyse_Result.opt_str = str;
        WordAnalyse_Result.str_len = str.length();
    }

    return WordAnalyse_Result;
}

