#include <iostream>
#include <string>
#include <map>
#include <vector>

#define LETTER_NUM 26
#define DIGIT_NUM 10

using namespace std;

// 用于映射
struct node {
    int state;
    char ch;
};

vector<node> nodeList; // 存储可合法转换的状态 state = 1 or 2
map<node, int> mp; // 存储映射关系
map<int, bool> isAccept; // 是否为接收状态的映射

string lower_letter_list = "abcdefghijklmnopqrstuvwxyz";
string upper_letter_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string number_list = "0123456789";

void init()
{
    for(int i = 0; i < LETTER_NUM; i++) {
        struct node tmpNode1, tmpNode2, tmpNode3, tmpNode4;

        tmpNode1.state = 1;
        tmpNode1.ch = upper_letter_list[i];

        tmpNode2.state = 1;
        tmpNode2.ch = lower_letter_list[i];

        tmpNode3.state = 2;
        tmpNode3.ch = upper_letter_list[i];

        tmpNode4.state = 2;
        tmpNode4.ch = upper_letter_list[i];

        nodeList.push_back(tmpNode1);
        nodeList.push_back(tmpNode2);
        nodeList.push_back(tmpNode3);
        nodeList.push_back(tmpNode4);
    }

    for(int i = 0; i < DIGIT_NUM; i++) {
        node tmpNode;

        tmpNode.state = 2;
        tmpNode.ch = number_list[i];

        nodeList.push_back(tmpNode);
    }

    // 字母数字对状态2的映射
    for(int i = 0; i < nodeList.size(); i++) {
        if(nodeList[i].state == 1) {
            mp[nodeList[i]] = 2;
        }
        else if(nodeList[i].state == 2) {
            mp[nodeList[i]] = 2;
        }
    }

    // 对状态3的映射,如果map中不存在的映射关系，则转换成状态3

    // isAccept初始化1 2 为 false , 3 true
    isAccept[1] = false;
    isAccept[2] = false;
    isAccept[3] = true;

}

/*
    state 1 2 3
    T[state, ch] 当 ch 为 letter 时，state 由1转换为2
    Accept
*/
void recognize(string str)
{
    int state = 1;
    int i = 0;
    string res = "failed!!!";
    char curCh = str[i];

    // 当前状态不是接受状态时可以执行循环 false时可执行
    while(!isAccept[state]) {
        struct node newNode;
        newNode.state = state;
        newNode.ch = curCh;

        state = mp[newNode];
        // 非法映射
        if(!state) {
            state = 3;
            break;
        }

        curCh = str[++i];
    }

    res = str.substr(0, i);
    cout << "string output: " << res << endl;
}

int main()
{
    string input;
    cin >> input;

    // 初始化状态机
    init();

    // 词法分析
    recognize(input);

    return 0;
}