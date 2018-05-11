#define LOCAL
#include "Identifier_stateMachine.h"
#include "keywords_stateMachine.h"
#include "symbols_stateMachine.h"
#include "Decimal_StateMachine.h"

/**
================================================================================================================================
状态机实例化
================================================================================================================================
*/

Identifier_StateMachine identifier_statemachine; // Identifier
keywords_StateMachine keywords_statemachine; // 关键字
symbols_StateMachine symbols_statemachine; // 符号
Decimal_StateMachine decimal_statemachine; // 浮点数

/**
================================================================================================================================
*/


/**
================================================================================================================================
全局变量声明
================================================================================================================================
*/

int line = 1; // 标记代码当前行数

/**
================================================================================================================================
*/


/**
    状态机初始化
*/
void initialize()
{
	identifier_statemachine.init();
	decimal_statemachine.init();
	symbols_statemachine.init();
}


/**
    打印解析结果
    @params id 解析出的词对应的类型ID
    @parmas res_str 解析出的词
*/
void print(int id, std::string res_str)
{
    std::cout << "ID: " << id << std::endl;
    std::cout << "String output: " << res_str << std::endl;
    std::cout << "================================================================================================================================" << std::endl;
}


int main()
{
    #ifdef LOCAL
    freopen("test1.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // LOCAL

	initialize();

	std::string input;

	while(std::cin >> input) {

        //std::cout << "line " << line << " >> " << std::endl;

        // 代码行数处理


        std::cout << "Current Input: " << input << std::endl;

        // int a=b
        // 获得 a=b 字符串，需要将此字符串解析到为0为止，或者所有的状态机都无法解析为止
        while (true)
        {
            std::cout << "input: " << input << std::endl;

            Result output;
            // 关键字解析
            output = keywords_statemachine.keywords_recognize(input);
            if (output.ID != -1) {
                print(output.ID, output.opt_str);
                // 解析成功后，如果此字符串没有完全解析，将已经解析出来的字符串截掉，取后面部分
                if (output.str_len < input.length())
                {
                    input = input.substr(output.str_len);
                    continue;
                }
                else
                {
                    // 此字符串已经完全解析了
                    break;
                }
            }

            // 符号解析
            output = symbols_statemachine.symbols_recognize(input);
            if (output.ID != -1) {
                print(output.ID, output.opt_str);
                // 解析成功后，如果此字符串没有完全解析，将已经解析出来的字符串截掉，取后面部分
                if (output.str_len < input.length())
                {
                    input = input.substr(output.str_len);
                    continue;
                }
                else
                {
                    // 此字符串已经完全解析了
                    break;
                }
            }

            // 浮点数解析
            output = decimal_statemachine.decimal_recognize(input);
            if(output.ID != -1)
            {
                print(output.ID, output.opt_str);
                // 解析成功后，如果此字符串没有完全解析，将已经解析出来的字符串截掉，取后面部分
                if (output.str_len < input.length())
                {
                    input = input.substr(output.str_len);
                    continue;
                }
                else
                {
                    // 此字符串已经完全解析了
                    break;
                }
            }

            // 调用Identifier分析
            output = identifier_statemachine.identifier_recognize(input);
            if (output.ID != -1) {
                print(output.ID, output.opt_str);
                // 解析成功后，如果此字符串没有完全解析，将已经解析出来的字符串截掉，取后面部分
                if (output.str_len < input.length())
                {
                    input = input.substr(output.str_len);
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
                print(output.ID, output.opt_str);
                break;
            }

        }

	}

	return 0;
}
