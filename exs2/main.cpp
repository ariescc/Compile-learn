/**
    �﷨������

    exs1�����������Ϊ�˳�������룬��������������ӳ�䣺

        ILLEGAL_STRING            1000        �ʷ���������ĵ���
        IDENTIFIER_STATEMACHINE   1001        Identifier����
        DECIMAL_STATEMACHINE      1002        ����������
        KEYWORDS_STATEMACHINE     1003        �ؼ���
        SYMBOLS_STATEMACHINE      1004        ����

    �﷨�����Ľ��Ϊ���﷨��
*/

#define LOCAL
#include <iostream>
#include "resource.h"

using namespace std;

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // LOCAL


    return 0;
}
