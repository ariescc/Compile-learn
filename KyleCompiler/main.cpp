#define LOCAL
#include <iostream>
#include <stdio.h>
#include "Word_Analyser.h"

int line = 1;

int main()
{
    #ifdef LOCAL
    freopen("test1.txt", "r", stdin);
    #endif // LOCAL

    // ================================================================================================================================
    // �ʷ�����
    Word_Analyser word_analyser;

    std::string input;

    while (getline(std::cin, input))
    {
        word_analyser.GetWordList(input, line);
        line++;
    }

    // word_analyser.print_word_result(); // ��ӡ�ʷ��������

    std::vector<WordAnalyse_Result> word_list = word_analyser.wordanalyse_results; // �ʷ�����������﷨��������


    // ================================================================================================================================
    // �﷨����


    return 0;
}
