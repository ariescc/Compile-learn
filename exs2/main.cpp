/**
    语法分析器

    exs1的输出序列作为此程序的输入，单词类型做如下映射：

        ILLEGAL_STRING            1000        词法分析错误的单词
        IDENTIFIER_STATEMACHINE   1001        Identifier类型
        DECIMAL_STATEMACHINE      1002        浮点数类型
        KEYWORDS_STATEMACHINE     1003        关键字
        SYMBOLS_STATEMACHINE      1004        符号

    语法分析的结果为：语法树
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
