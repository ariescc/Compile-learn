#define LOCAL
#include <iostream>
#include <stdio.h>
#include "Word_Analyser.h"
#include "Parser.h"

int line = 1;

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    #endif // LOCAL

    // ================================================================================================================================
    // 词法分析
    Word_Analyser word_analyser;

    std::string input;

    while (getline(std::cin, input))
    {
        word_analyser.GetWordList(input, line);
        line++;
    }

    //word_analyser.print_word_result(); // 打印词法分析结果

    std::vector<WordAnalyse_Result> word_list = word_analyser.wordanalyse_results; // 词法分析输出，语法分析输入

    // ================================================================================================================================
    // 语法分析

    // 初始化语法分析器
    Parser parser;
    parser.init(word_list);

    treeNode * root = parser.parser_solve();
    //std::cout << root << std::endl;

    return 0;
}
