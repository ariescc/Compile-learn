#define LOCAL
#include "Identifier_stateMachine.h"
#include "keywords_stateMachine.h"
#include "symbols_stateMachine.h"
#include "Decimal_StateMachine.h"

Identifier_StateMachine identifier_statemachine; // Identifier
keywords_StateMachine keywords_statemachine; // �ؼ���
symbols_StateMachine symbols_statemachine; // ����
Decimal_StateMachine decimal_statemachine; // ������

void initialize()
{
	identifier_statemachine.init();
	decimal_statemachine.init();
	symbols_statemachine.init();
}

// ��ӡ���
void print(int id, std::string res_str)
{
    std::cout << "ID: " << id << std::endl;
    std::cout << "String output: " << res_str << std::endl;
    std::cout << "=====================================================================" << std::endl;
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
        std::cout << input << std::endl;

        // int a=b
        // ��� a=b �ַ�������Ҫ�����ַ���������Ϊ0Ϊֹ���������е�״̬�����޷�����Ϊֹ
        while (true)
        {
            std::cout << "input: " << input << std::endl;

            Result output;
            // �ؼ��ֽ���
            output = keywords_statemachine.keywords_recognize(input);
            if (output.ID != -1) {
                print(output.ID, output.opt_str);
                // �����ɹ���������ַ���û����ȫ���������Ѿ������������ַ����ص���ȡ���沿��
                if (output.str_len < input.length())
                {
                    input = input.substr(output.str_len);
                    continue;
                }
                else
                {
                    // ���ַ����Ѿ���ȫ������
                    //std::cout << "keywords" << std::endl;
                    break;
                }
            }

            // ���Ž���
            output = symbols_statemachine.symbols_recognize(input);
            if (output.ID != -1) {
                print(output.ID, output.opt_str);
                // �����ɹ���������ַ���û����ȫ���������Ѿ������������ַ����ص���ȡ���沿��
                if (output.str_len < input.length())
                {
                    input = input.substr(output.str_len);
                    continue;
                }
                else
                {
                    // ���ַ����Ѿ���ȫ������
                    //std::cout << "symbols" << std::endl;
                    break;
                }
            }

            // ����������
            output = decimal_statemachine.decimal_recognize(input);
            if(output.ID != -1)
            {
                print(output.ID, output.opt_str);
                // �����ɹ���������ַ���û����ȫ���������Ѿ������������ַ����ص���ȡ���沿��
                if (output.str_len < input.length())
                {
                    input = input.substr(output.str_len);
                    //std::cout << "input: " << input << std::endl;
                    continue;
                }
                else
                {
                    // ���ַ����Ѿ���ȫ������
                    //std::cout << "decimal" << std::endl;
                    break;
                }
            }

            // ����Identifier����
            output = identifier_statemachine.identifier_recognize(input);
            if (output.ID != -1) {
                print(output.ID, output.opt_str);
                //std::cout << "iden_len: " << output.str_len << std::endl;
                // �����ɹ���������ַ���û����ȫ���������Ѿ������������ַ����ص���ȡ���沿��
                if (output.str_len < input.length())
                {
                    input = input.substr(output.str_len);
                    continue;
                }
                else
                {
                    // ���ַ����Ѿ���ȫ������
                    //std::cout << "identifier" << std::endl;
                    break;
                }
            }
            else{
                // ����״̬�����޷������ˣ���ֹͣ�Ե�ǰ�ַ����Ľ�����������ȡ
                print(output.ID, output.opt_str);
                break;
            }

            //std::cout << "length: " << input.length() << std::endl;
        }

	}

	return 0;
}