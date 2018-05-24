#include "Identifier_stateMachine.h"

Identifier_StateMachine::Identifier_StateMachine() {}

/**
    Identifier状态机初始化
*/
void Identifier_StateMachine::init()
{

	isAccept[1] = false;
	isAccept[2] = false;
	isAccept[3] = false;
	isAccept[4] = true;


	for (int i = 0; i < LETTER_NUM; i++)
	{
		Relation relation1, relation2,
			relation3, relation4,
			relation5, relation6;

		relation1.state = 1;
		relation1.ch = upper_letter_list[i];

		relation2.state = 1;
		relation2.ch = lower_letter_list[i];

		relation3.state = 2;
		relation3.ch = upper_letter_list[i];

		relation4.state = 2;
		relation4.ch = lower_letter_list[i];

		relation5.state = 3;
		relation5.ch = upper_letter_list[i];

		relation6.state = 3;
		relation6.ch = lower_letter_list[i];



		relations.push_back(relation1);
		relations.push_back(relation2);
		relations.push_back(relation3);
		relations.push_back(relation4);
		relations.push_back(relation5);
		relations.push_back(relation6);
	}


	for (int i = 0; i < DIGIT_NUM; i++)
	{
		Relation relation1, relation2;

		relation1.state = 2;
		relation1.ch = number_list[i];

		relation2.state = 3;
		relation2.ch = number_list[i];

		relations.push_back(relation1);
		relations.push_back(relation2);
	}

	Relation relation;
	relation.state = 2;
	relation.ch = '_';

	relations.push_back(relation);



	/*
	============================================================================================================
	map
	============================================================================================================
	*/
	for (int i = 0; i < relations.size(); i++)
	{
		if (relations[i].state == 2 && relations[i].ch == '_')
		{
			mp[relations[i]] = 3;
		}
		else if (relations[i].state == 2 && relations[i].ch != '_')
		{
			mp[relations[i]] = 2;
		}
		else if (relations[i].state == 1)
		{
			mp[relations[i]] = 2;
		}
		else if (relations[i].state == 3)
		{
			mp[relations[i]] = 2;
		}
	}

	/*
	print map

	std::map<Relation, int>::iterator p;
	std::cout << "map size: " << mp.size() << std::endl;
	for (p = mp.begin(); p != mp.end(); p++)
	{
		std::cout << (p->first).state << " " << (p->first).ch << " => " << p->second << std::endl;
	}
	*/
}

/**
    Identifier状态机解析
    Identifier 只起到识别单词的作用：解析的结果可能是Identifier或是关键字

    在关键字状态机函数中判断解析出的单词是Identifier，还是关键字

    @return WordAnalyse_Result 有效的返回：识别出的单词

*/
WordAnalyse_Result Identifier_StateMachine::identifier_recognize(std::string str)
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

		if (!mp[relation])
		{
			break;
		}

		state = mp[relation];
		curCh = str[++i];
	}

	res = str.substr(0, i);

	WordAnalyse_Result output;
	if (state != 3 && state != 2)
	{
	    output.str_len = 1;
		output.ID = ILLEGAL_STRING;
		output.opt_str = str[0];
	}
	else
	{
	    output.str_len = i;
		output.ID = IDENTIFIER_STATEMACHINE;
		output.opt_str = res;
	}

	return output;
}

