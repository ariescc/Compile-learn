#include "keywords_stateMachine.h"

keywords_StateMachine::keywords_StateMachine() {}

void keywords_StateMachine::init()
{
    /*
    ==============================================================================================================
    关键字插入到集合中
    ==============================================================================================================


    key_words.insert("thread");
    key_words.insert("features");
    key_words.insert("flows");
    key_words.insert("properties");
    key_words.insert("end");
    key_words.insert("none");
    key_words.insert("in");
    key_words.insert("out");
    key_words.insert("data");
    key_words.insert("port");
    key_words.insert("event");
    key_words.insert("parameter");
    key_words.insert("flow");
    key_words.insert("source");
    key_words.insert("sink");
    key_words.insert("path");
    key_words.insert("constant");
    key_words.insert("access");
    */
}

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
