#define LOCAL
#include "Identifier_stateMachine.h"
#include "keywords_stateMachine.h"
#include "symbols_stateMachine.h"
#include "Decimal_StateMachine.h"

/**
================================================================================================================================
    �ַ����ָ��ʵ��
================================================================================================================================
*/
std::vector<std::string> SplitString(const std::string& s, const std::string& c)
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
================================================================================================================================
״̬��ʵ����
================================================================================================================================
*/

Identifier_StateMachine identifier_statemachine; // Identifier
keywords_StateMachine keywords_statemachine; // �ؼ���
symbols_StateMachine symbols_statemachine; // ����
Decimal_StateMachine decimal_statemachine; // ������

/**
================================================================================================================================
*/


/**
================================================================================================================================
ȫ�ֱ�������
================================================================================================================================
*/

int line = 1; // ��Ǵ��뵱ǰ����

/**
================================================================================================================================
*/


/**
    ״̬����ʼ��
*/
void initialize()
{
	identifier_statemachine.init();
	decimal_statemachine.init();
	symbols_statemachine.init();
}


/**
    ��ӡ�������
    @params id �������Ĵʶ�Ӧ������ID
    @parmas res_str �������Ĵ�
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
    freopen("test3.txt", "r", stdin);
    freopen("out3.txt", "w", stdout);
    #endif // LOCAL

	initialize();

	std::string input;

	while(getline(std::cin, input)) {
        // ������������
        std::cout << "line " << line++ << " >> " << std::endl;

        // ���ͷ���ո�
        int c_index = 0;
        while (input[c_index] == ' ' || input[c_index] == '\t')
        {
            c_index++;
        }
        input = input.substr(c_index);

        //std::cout << "Current Input: " << input << std::endl;

        // ʹ�ÿո�ָ�ÿһ���ַ���
        std::vector<std::string> inputs = SplitString(input, " ");

        for (int t = 0; t < inputs.size(); t++)
        {
            std::string input_cur = inputs[t];

            //std::cout << input_cur << std::endl;

            // int a=b
            // ��� a=b �ַ�������Ҫ�����ַ���������Ϊ0Ϊֹ���������е�״̬�����޷�����Ϊֹ
            while (true)
            {
                std::cout << "input: " << input_cur << std::endl;

                Result output;
                // �ؼ��ֽ���
                output = keywords_statemachine.keywords_recognize(input_cur);
                if (output.ID != -1) {
                    print(output.ID, output.opt_str);
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
                if (output.ID != -1) {
                    print(output.ID, output.opt_str);
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
                if(output.ID != -1)
                {
                    print(output.ID, output.opt_str);
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

                // ����Identifier����
                output = identifier_statemachine.identifier_recognize(input_cur);
                if (output.ID != -1) {
                    print(output.ID, output.opt_str);
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
                    print(output.ID, output.opt_str);
                    break;
                }

            }
        }


	}

	return 0;
}
