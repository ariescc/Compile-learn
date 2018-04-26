/*
    词法分割
*/

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// 判断是否是字母
bool isLetter(char ch)
{
    if((ch > 'a' && ch < 'z') || (ch > 'A' && ch < 'Z')) {
        return true;
    }
    return false;
}

// 判断是否是数字
bool isDigit(char ch) {
    if(ch > '0' && ch < '9') {
        return true;
    }
    return false;
}

void judge(string str)
{
    string res = "";
    // 先判断第一位是否是 letter
    if(isLetter(str[0])) {
        int i = 1;
        while(isLetter(str[i]) || isDigit(str[i])) {
            ++i;
        }

        // 当出现不合法字符，截取之前的字符串
        res = str.substr(0, i);
        cout << "string output: " << res << endl;

    }
    else {
        // 不是letter，不合法
        cout << "first char isn't a letter!" << endl;
    }
}

int main()
{
    string input;
    cin >> input;
    judge(input);
    return 0;
}

