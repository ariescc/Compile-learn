#define LOCAL
#include "Word_Analyser.h"
#include <stdio.h>

Word_Analyser::Word_Analyser()
{
    initialize();
}

/**
    状态机初始化
*/
void Word_Analyser::initialize()
{
    identifier_statemachine.init();
	decimal_statemachine.init();
	symbols_statemachine.init();
	keywords_statemachine.init();
}

/**
    字符串分割
*/
std::vector<std::string> Word_Analyser::SplitString(const std::string& s, const std::string& c)
{
    std::vector<std::string> v;
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
    v.push_back(s.substr(pos1, pos2-pos1));

    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
    v.push_back(s.substr(pos1));

    return v;
}

/**
    打印词法分析结果
*/
void Word_Analyser::print_word_result()
{
    #ifdef LOCAL
    freopen("output_word_result.txt", "w", stdout);
    #endif // LOCAL

    for (int i = 0; i < wordanalyse_results.size(); i++)
    {
        std::cout << "line:" << wordanalyse_results[i].line << " " <<  wordanalyse_results[i].ID << " " << wordanalyse_results[i].opt_str << std::endl;
    }
}

/**
    获得词法分析结果，单词列表。
    并作为语法分析的输入

    @params input 读取的当前行的代码
    @params ln  当前单词所处代码行数
*/
std::vector<WordAnalyse_Result> Word_Analyser::GetWordList(std::string input, int ln)
{
    // 清除头部空格
    int c_index = 0;
    while (input[c_index] == ' ' || input[c_index] == '\t')
    {
        c_index++;
    }
    input = input.substr(c_index);

    // 使用空格分割每一行字符串
    std::vector<std::string> inputs = SplitString(input, " ");

    for (int t = 0; t < inputs.size(); t++)
    {
        std::string input_cur = inputs[t];

        // int a=b
        // 获得 a=b 字符串，需要将此字符串解析到为0为止，或者所有的状态机都无法解析为止
        while (true)
        {
            WordAnalyse_Result output;

            // Identifier解析
            output = identifier_statemachine.identifier_recognize(input_cur);
            if (output.ID != ILLEGAL_STRING)
            {
                std::cout << "sb" << std::endl;
                std::string word = output.opt_str;

                // 判断Identifier解析出的单词是关键字还是Identifier
                output = keywords_statemachine.keywords_recognize(word);
                output.line = ln;
                wordanalyse_results.push_back(output);

                // 解析成功后，如果此字符串没有完全解析，将已经解析出来的字符串截掉，取后面部分
                if (output.str_len < input_cur.length())
                {
                    input_cur = input_cur.substr(output.str_len);
                    continue;
                }
                else
                {
                    // 此字符串已经完全解析了
                    break;
                }
            }

            // 符号解析
            output = symbols_statemachine.symbols_recognize(input_cur);
            std::cout << "symbols" << std::endl;
            std::cout << output.ID << std::endl;
            std::cout << output.opt_str << std::endl;
            if (output.ID != ILLEGAL_STRING) {
                std::cout << "qb" << std::endl;
                wordanalyse_results.push_back(output);
                // 解析成功后，如果此字符串没有完全解析，将已经解析出来的字符串截掉，取后面部分
                if (output.str_len < input_cur.length())
                {
                    input_cur = input_cur.substr(output.str_len);
                    continue;
                }
                else
                {
                    // 此字符串已经完全解析了
                    break;
                }
            }

            // 浮点数解析
            output = decimal_statemachine.decimal_recognize(input_cur);
            std::cout << "decimal" << std::endl;
            std::cout << output.ID << std::endl;
            std::cout << output.opt_str << std::endl;
            if(output.ID != ILLEGAL_STRING)
            {
                std::cout << "2b" << std::endl;
                wordanalyse_results.push_back(output);
                // 解析成功后，如果此字符串没有完全解析，将已经解析出来的字符串截掉，取后面部分
                if (output.str_len < input_cur.length())
                {
                    input_cur = input_cur.substr(output.str_len);
                    continue;
                }
                else
                {
                    // 此字符串已经完全解析了
                    break;
                }
            }
            else{
                // 所有状态机都无法解析了，则停止对当前字符串的解析，继续读取
                wordanalyse_results.push_back(output);
                if (output.str_len < input_cur.length())
                {
                    input_cur = input_cur.substr(output.str_len);
                    continue;
                }
                else
                {
                    break;
                }
            }

        }
    }
    return wordanalyse_results;
}
