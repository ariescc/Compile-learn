#include "Decimal_StateMachine.h"

Decimal_StateMachine::Decimal_StateMachine() {}

/**
    ״̬����ʼ��
*/
void Decimal_StateMachine::init()
{
    // ȷ������״̬
    isAccept[1] = false;
    isAccept[2] = false;
    isAccept[3] = false;
    isAccept[4] = false;
    isAccept[5] = false;
    isAccept[6] = true;

    // ����ӳ��
    for (int i = 0; i < DIGIT_NUM; i++) {
        Relation relation1, relation2, relation3, relation4, relation5;

        relation1.state = 1;
        relation1.ch = number_list[i];

        relation2.state = 2;
        relation2.ch = number_list[i];

        relation3.state = 3;
        relation3.ch = number_list[i];

        relation4.state = 4;
        relation4.ch = number_list[i];

        relation5.state = 5;
        relation5.ch = number_list[i];

        // ����ʼ״̬�봥���ַ�ӳ���ϵ���뵽relations��
        relations.push_back(relation1);
        relations.push_back(relation2);
        relations.push_back(relation3);
        relations.push_back(relation4);
        relations.push_back(relation5);
    }


    Relation relation1, relation2, relation3;
    // С����ӳ��
    relation1.state = 3;
    relation1.ch = '.';

    // sign(+|-)ӳ��
    relation2.state = 1;
    relation2.ch = '+';

    relation3.state = 1;
    relation3.ch = '-';

    // ����ʼ״̬�봥���ַ�ӳ���ϵ���뵽relations��
    relations.push_back(relation1);
    relations.push_back(relation2);
    relations.push_back(relation3);


    /*
    ===================================================================================================================
    ��ʼ״̬�봥���ַ����뵽map�У�ӳ�䵽Ŀ��״̬
    ===================================================================================================================
    */
    for (int i = 0; i < relations.size(); i++)
    {
        // �����ַ�Ϊ+��- 1=��2
        if (relations[i].ch == '+' || relations[i].ch == '-')
        {
            mp[relations[i]] = 2;
        }
        // 1=>3
        else if (relations[i].state == 1 && relations[i].ch != '+' && relations[i].ch != '-')
        {
            mp[relations[i]] = 3;
        }
        // 2 => 3
        else if (relations[i].state == 2)
        {
            mp[relations[i]] = 3;
        }
        // 3 => 4
        else if (relations[i].ch == '.')
        {
            mp[relations[i]] = 4;
        }
        // 3 => 3
        else if (relations[i].state == 3 && relations[i].ch != '.')
        {
            mp[relations[i]] = 3;
        }
        // 4 => 5 or 5 => 5
        else if (relations[i].state == 4 || relations[i].state == 5)
        {
            mp[relations[i]] = 5;
        }
    }

    /*
    std::map<Relation, int>::iterator p;
    for(p = mp.begin(); p != mp.end(); p++) {
        std::cout << (p -> first).state << " " << (p -> first).ch << " " << p -> second << std::endl;
    }
    */
}

/**
    ������״̬������������
    @params str Ҫ�������ַ���
*/
Result Decimal_StateMachine::decimal_recognize(std::string str)
{
    int state = 1;
	int i = 0;
	std::string res = "failed!";
	char curCh = str[i];

	while (!isAccept[state] && i < str.length())
	{
		Relation relation;

		relation.state = state;
		relation.ch = curCh;

		state = mp[relation];

		// ���ӳ��״̬�����ڣ�Ĭ��map��Ϊ0
		if (!state)
		{
			state = 6;
			break;
		}
		curCh = str[++i];
	}

	res = str.substr(0, i);

	Result output;
	if (!i)
	{
	    // �ص�һ�������ַ�
	    output.str_len = 1;
		output.ID = ILLEGAL_STRING;
		output.opt_str = str[0];
	}
	else
	{
	    output.str_len = i;
		output.ID = DECIMAL_STATEMACHINE;
		output.opt_str = res;
	}

	return output;
}
