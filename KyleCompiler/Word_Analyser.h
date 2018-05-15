#pragma once

#include "Identifier_stateMachine.h"
#include "keywords_stateMachine.h"
#include "symbols_stateMachine.h"
#include "Decimal_StateMachine.h"


class Word_Analyser {
public:
    // ==================================================================================================================================
    // 状态机实例化
    Identifier_StateMachine identifier_statemachine; // Identifier
    keywords_StateMachine keywords_statemachine; // 关键字
    symbols_StateMachine symbols_statemachine; // 符号
    Decimal_StateMachine decimal_statemachine; // 浮点数

    std::vector<WordAnalyse_Result> wordanalyse_results;

    // =================================================================================================================================
    // 词法分析相关方法声明

    Word_Analyser(); // 构造函数

    void initialize(); // 初始化状态机

    std::vector<WordAnalyse_Result> GetWordList(std::string input, int ln); // 词法分析获取单词序列
    void print_word_result();

    std::vector<std::string> SplitString(const std::string& s, const std::string& c); // 字符串分割

};
