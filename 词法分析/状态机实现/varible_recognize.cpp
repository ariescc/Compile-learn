#include <iostream>
#include <map>
#include <vector>
#include "relation.h"

#define LETTER_NUM 26
#define DIGIT_NUM 10

using namespace std;

std::string lower_letter_list = "abcdefghijklmnopqrstuvwxyz";
std::string upper_letter_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string number_list = "0123456789";

// 存储可合法转换的状态 state = 1 or 2
vector<Relation> relations;
// 存储映射关系
map<Relation, int> mp;
// 是否为接受状态
map<int, bool> isAccept;

void init()
{
    // 对所有的字母创建状态1or2的映射
    // 对所有0-9数字创建状态为2的映射
    for(int i = 0; i < LETTER_NUM; i++) {
        Relation relation1, relation2, relation3, relation4;

        relation1.state = 1;
        relation1.ch = upper_letter_list[i];

        relation2.state = 1;
        relation2.ch = lower_letter_list[i];

        relation3.state = 2;
        relation3.ch = upper_letter_list[i];

        relation4.state = 2;
        relation4.ch = lower_letter_list[i];

        relations.push_back(relation1);
        relations.push_back(relation2);
        relations.push_back(relation3);
        relations.push_back(relation4);
    }

    /*
    for(int i = 0; i < relations.size(); i++) {
        cout << relations[i].state << " " << relations[i].ch << endl;
    }
    */

    for(int i = 0; i < DIGIT_NUM; i++) {
        Relation relation;

        relation.state = 2;
        relation.ch = number_list[i];

        relations.push_back(relation);
    }

    // cout << "vector size: " << relations.size() << endl;

    // 字母和数字对目标状态2进行映射
    for(int i = 0; i < relations.size(); i++) {
        // cout << i << " " << relations[i].state << " " << relations[i].ch << endl;
        mp[relations[i]] = 2;
    }

    // test output
    /*
    map<Relation, int>::iterator p;
    cout << "map size: " << mp.size() << endl;
    for(p = mp.begin(); p != mp.end(); p++) {
        cout << "map output: " << (p -> first).state << " " << (p -> first).ch << " " << p -> second << endl;
    }
    */

    // 当map映射的对象的目标值为0，即未设定目标状态，此状态为接受状态3

    // isAccept初始化1 2 为 false， 3为true
    isAccept[1] = false;
    isAccept[2] = false;
    isAccept[3] = true;

}

/*
    state 1 2 3
    T[state, ch] 当 ch 为 letter 时，state 由 1 转换为 2
*/
void recognize(string str)
{
    int state = 1;
    int i = 0;
    string res = "failed!!!";
    char curCh = str[i];

    // test
    Relation test;
    test.state = 1;
    test.ch = '1';
    cout << "test: " << mp[test] << endl;

    // 当前状态不是接受状态时可以执行循环 false时可执行
    while(!isAccept[state] && i < str.length()) {

        cout << "state: " << state << endl;

        Relation relation;
        relation.state = state;
        relation.ch = curCh;

        cout << "test case: " << relation.state << " " << relation.ch << endl;

        state = mp[relation];
        // 非法映射
        if(!state) {
            state = 3;
            break;
        }
        curCh = str[++i];
    }

    res = str.substr(0, i);
    cout << " String output: " << res << endl;
}

int main()
{
    init();

    string input;
    cin >> input;

    recognize(input);

    return 0;
}