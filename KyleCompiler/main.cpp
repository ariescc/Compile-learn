#define LOCAL
#include <iostream>
#include <stdio.h>
#include "Word_Analyser.h"
#include "Parser.h"

int line = 1;

int main()
{
    #ifdef LOCAL
    freopen("test1.txt", "r", stdin);
    freopen("SyntaxOut.txt", "w", stdout);
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

    // std::cout << word_list.size() << std::endl;

    // ================================================================================================================================
    // 语法分析

    // 初始化语法分析器
    Parser parser;
    parser.init(word_list);

    treeNode * root = parser.parser_solve();
    //std::cout << root << std::endl;

    // 递归打印语法树（后序遍历
    parser.print_parser_tree(root, 0);

    return 0;
}
