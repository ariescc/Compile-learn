#define LOCAL
#include "Word_Analyser.h"
#include <stdio.h>

Word_Analyser::Word_Analyser()
{
    initialize();
}

/**
    ״̬����ʼ��
*/
void Word_Analyser::initialize()
{
    identifier_statemachine.init();
	decimal_statemachine.init();
	symbols_statemachine.init();
	keywords_statemachine.init();
}

/**
    �ַ����ָ�
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
    ��ӡ�ʷ��������
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
    ��ôʷ���������������б�
    ����Ϊ�﷨����������

    @params input ��ȡ�ĵ�ǰ�еĴ���
    @params ln  ��ǰ����������������
*/
std::vector<WordAnalyse_Result> Word_Analyser::GetWordList(std::string input, int ln)
{
    // ���ͷ���ո�
    int c_index = 0;
    while (input[c_index] == ' ' || input[c_index] == '\t')
    {
        c_index++;
    }
    input = input.substr(c_index);

    // ʹ�ÿո�ָ�ÿһ���ַ���
    std::vector<std::string> inputs = SplitString(input, " ");

    for (int t = 0; t < inputs.size(); t++)
    {
        std::string input_cur = inputs[t];

        // int a=b
        // ��� a=b �ַ�������Ҫ�����ַ���������Ϊ0Ϊֹ���������е�״̬�����޷�����Ϊֹ
        while (true)
        {
            WordAnalyse_Result output;

            // Identifier����
            output = identifier_statemachine.identifier_recognize(input_cur);
            if (output.ID != ILLEGAL_STRING)
            {
                std::cout << "sb" << std::endl;
                std::string word = output.opt_str;

                // �ж�Identifier�������ĵ����ǹؼ��ֻ���Identifier
                output = keywords_statemachine.keywords_recognize(word);
                output.line = ln;
                wordanalyse_results.push_back(output);

                // �����ɹ���������ַ���û����ȫ���������Ѿ������������ַ����ص���ȡ���沿��
                if (output.str_len < input_cur.length())
                {
                    input_cur = input_cur.substr(output.str_len);
                    continue;
                }
                else
                {
                    // ���ַ����Ѿ���ȫ������
                    break;
                }
            }

            // ���Ž���
            output = symbols_statemachine.symbols_recognize(input_cur);
            std::cout << "symbols" << std::endl;
            std::cout << output.ID << std::endl;
            std::cout << output.opt_str << std::endl;
            if (output.ID != ILLEGAL_STRING) {
                std::cout << "qb" << std::endl;
                wordanalyse_results.push_back(output);
                // �����ɹ���������ַ���û����ȫ���������Ѿ������������ַ����ص���ȡ���沿��
                if (output.str_len < input_cur.length())
                {
                    input_cur = input_cur.substr(output.str_len);
                    continue;
                }
                else
                {
                    // ���ַ����Ѿ���ȫ������
                    break;
                }
            }

            // ����������
            output = decimal_statemachine.decimal_recognize(input_cur);
            std::cout << "decimal" << std::endl;
            std::cout << output.ID << std::endl;
            std::cout << output.opt_str << std::endl;
            if(output.ID != ILLEGAL_STRING)
            {
                std::cout << "2b" << std::endl;
                wordanalyse_results.push_back(output);
                // �����ɹ���������ַ���û����ȫ���������Ѿ������������ַ����ص���ȡ���沿��
                if (output.str_len < input_cur.length())
                {
                    input_cur = input_cur.substr(output.str_len);
                    continue;
                }
                else
                {
                    // ���ַ����Ѿ���ȫ������
                    break;
                }
            }
            else{
                // ����״̬�����޷������ˣ���ֹͣ�Ե�ǰ�ַ����Ľ�����������ȡ
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
