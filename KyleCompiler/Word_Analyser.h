#pragma once

#include "Identifier_stateMachine.h"
#include "keywords_stateMachine.h"
#include "symbols_stateMachine.h"
#include "Decimal_StateMachine.h"


class Word_Analyser {
public:
    // ==================================================================================================================================
    // ״̬��ʵ����
    Identifier_StateMachine identifier_statemachine; // Identifier
    keywords_StateMachine keywords_statemachine; // �ؼ���
    symbols_StateMachine symbols_statemachine; // ����
    Decimal_StateMachine decimal_statemachine; // ������

    std::vector<WordAnalyse_Result> wordanalyse_results;

    // =================================================================================================================================
    // �ʷ�������ط�������

    Word_Analyser(); // ���캯��

    void initialize(); // ��ʼ��״̬��

    std::vector<WordAnalyse_Result> GetWordList(std::string input, int ln); // �ʷ�������ȡ��������
    void print_word_result();

    std::vector<std::string> SplitString(const std::string& s, const std::string& c); // �ַ����ָ�

};
