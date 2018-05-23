#include "symbols_stateMachine.h"

symbols_StateMachine::symbols_StateMachine() {}

/**
    (���ַ�)����״̬����ʼ��
*/
void symbols_StateMachine::init()
{
    /*
    ======================================================================================================================
    => ״̬����ʼ��
    ======================================================================================================================
    */
    isAccept1[1] = false;
    isAccept1[2] = false;
    isAccept1[3] = false;
    isAccept1[4] = true;

    Relation r1_1, r1_2;

    r1_1.state = 1;
    r1_1.ch = '=';

    r1_2.state = 2;
    r1_2.ch = '>';

    sym1[r1_1] = 2;
    sym1[r1_2] = 3;


    /*
    ======================================================================================================================
    +=> ״̬����ʼ��
    ======================================================================================================================
    */
    isAccept2[1] = false;
    isAccept2[2] = false;
    isAccept2[3] = false;
    isAccept2[4] = false;
    isAccept2[5] = true;

    Relation r2_1, r2_2, r2_3;

    r2_1.state = 1;
    r2_1.ch = '+';

    r2_2.state = 2;
    r2_2.ch = '=';

    r2_3.state = 3;
    r2_3.ch = '>';

    sym2[r2_1] = 2;
    sym2[r2_2] = 3;
    sym2[r2_3] = 4;


    /*
    ===========================================================================================
    :: 1:2:3 4
    ===========================================================================================
    */
    isAccept3[1] = false;
    isAccept3[2] = false;
    isAccept3[3] = false;
    isAccept3[4] = true;

    Relation r3_1, r3_2;

    r3_1.state = 1;
    r3_1.ch = ':';

    r3_2.state = 2;
    r3_2.ch = ':';

    sym3[r3_1] = 2;
    sym3[r3_2] = 3;

    /*
    ===========================================================================================
    -> 1 - 2 > 3 4
    ===========================================================================================
    */
    isAccept4[1] = false;
    isAccept4[2] = false;
    isAccept4[3] = false;
    isAccept4[4] = true;

    Relation r4_1, r4_2;

    r4_1.state = 1;
    r4_1.ch = '-';

    r4_2.state = 2;
    r4_2.ch = '>';

    sym4[r4_1] = 2;
    sym4[r4_2] = 3;


    /*
    ===========================================================================================
    :
    ===========================================================================================
    */
    isAccept5[1] = false;
    isAccept5[2] = false;
    isAccept5[3] = true;

    Relation r5_1;
    r5_1.state = 1;
    r5_1.ch = ':';

    sym5[r5_1] = 2;


    /*
    ===========================================================================================
    ;
    ===========================================================================================
    */
    isAccept6[1] = false;
    isAccept6[2] = false;
    isAccept6[3] = true;

    Relation r6_1;
    r6_1.state = 1;
    r6_1.ch = ';';

    sym6[r6_1] = 2;

    /*
    ===========================================================================================
    {
    ===========================================================================================
    */
    isAccept7[1] = false;
    isAccept7[2] = false;
    isAccept7[3] = true;

    Relation r7_1;
    r7_1.state = 1;
    r7_1.ch = '{';

    sym7[r7_1] = 2;


    /*
    ===========================================================================================
    }
    ===========================================================================================
    */
    isAccept8[1] = false;
    isAccept8[2] = false;
    isAccept8[3] = true;

    Relation r8_1;
    r8_1.state = 1;
    r8_1.ch = '}';

    sym8[r8_1] = 2;

    /*
    std::map<Relation, int>::iterator p;
    for (p = sym1.begin(); p != sym1.end(); p++)
    {
        std::cout << (p -> first).state << " " << (p -> first).ch << " " << p -> second << std::endl;
    }
    std::cout << std::endl;
    */

}

/**
    ����״̬�����ý�������
    @params isaccept ��ǰ״̬���Ľ���״̬
    @params mmp ��ǰ״̬������ʼ״̬�봥���ַ���ӳ���ϵ
*/
WordAnalyse_Result symbols_StateMachine::public_recognize(std::map<int, bool>& isaccept, std::map<Relation, int>& mmp, std::string str)
{
    int state = 1;
	int i = 0;
	std::string res = "failed!";
	char curCh = str[i];

	while (!isaccept[state] && i < str.length())
	{

		//std::cout << "state: " << state << std::endl;
		//std::cout << "char: " << curCh << std::endl;

		Relation relation;

		relation.state = state;
		relation.ch = curCh;

		state = mmp[relation];
        //std::cout << "state: " << state << std::endl;

		if (!state)
		{
			state = isaccept.size();
			break;
		}
		curCh = str[++i];
	}

	res = str.substr(0, i);

	WordAnalyse_Result output;
	if (!i)
	{
	    output.str_len = 1;
		output.ID = -1;
		output.opt_str = "Illegal string!";
	}
	else
	{
	        // "=>", "+=>", ";", ":", "::", "{", "}", "->"
        if(res == ";") output.ID = FEN;
        else if(res == "+=>") output.ID = PLUS_EQUAL_GREATER;
        else if(res == "=>") output.ID = EQUAL_GREATER;
        else if(res == ":") output.ID = MAO;
        else if(res == "::") output.ID = TWO_MAO;
        else if(res == "{") output.ID = LEFT_HUA_KH;
        else if(res == "}") output.ID = RIGHT_HUA_KH;
        else if(res == "->") output.ID = MISE_GREARER;
	    output.str_len = i;
		//output.ID = SYMBOLS_STATEMACHINE;
		output.opt_str = res;
	}

	//std::cout << output.ID << " " << output.opt_str << std:: endl;

	return output;

}


/**
    ���ż���ӳ���ж�
*/
WordAnalyse_Result symbols_StateMachine::symbols_recognize_set(std::string str)
{
    WordAnalyse_Result output;
    if (symbols.count(str) > 0)
    {
        output.str_len = 1;
        output.ID = SYMBOLS_STATEMACHINE;
        output.opt_str = str;
    }
    else
    {
        output.str_len = 1;
        output.ID = ILLEGAL_STRING;
        output.opt_str = str[0];
    }
    return output;
}


/**
    ������״̬�� = �����ж� + ���ַ�����״̬���ж�
*/
WordAnalyse_Result symbols_StateMachine::symbols_recognize(std::string str)
{
    std::vector<WordAnalyse_Result> WordAnalyse_Results; // ״̬����������������չ

    /*
    ========================================================================================================================
    ���ַ�״̬��ִ��
    ========================================================================================================================
    */

    // => ״̬��
    WordAnalyse_Result res1 = public_recognize(isAccept1, sym1, str);
    WordAnalyse_Results.push_back(res1);

    // +=> ״̬��
    WordAnalyse_Result res2 = public_recognize(isAccept2, sym2, str);
    WordAnalyse_Results.push_back(res2);

    // :: ״̬��
    WordAnalyse_Result res3 = public_recognize(isAccept3, sym3, str);
    WordAnalyse_Results.push_back(res3);
    //std::cout << "\"::\" > " << res3.ID << std::endl;

    // -> ״̬��
    WordAnalyse_Result res4 = public_recognize(isAccept4, sym4, str);
    WordAnalyse_Results.push_back(res4);

    // : ״̬��
    WordAnalyse_Result res5 = public_recognize(isAccept5, sym5, str);
    WordAnalyse_Results.push_back(res5);

    // ; ״̬��
    WordAnalyse_Result res6 = public_recognize(isAccept6, sym6, str);
    WordAnalyse_Results.push_back(res6);

    // { ״̬��
    WordAnalyse_Result res7 = public_recognize(isAccept7, sym7, str);
    WordAnalyse_Results.push_back(res7);

    // } ״̬��
    WordAnalyse_Result res8 = public_recognize(isAccept8, sym8, str);
    WordAnalyse_Results.push_back(res8);

    /*
    ========================================================================================================================
    ���ż����ж�
    ========================================================================================================================
    */
    WordAnalyse_Result res_set = symbols_recognize_set(str);
    WordAnalyse_Results.push_back(res_set);


    /*
    ========================================================================================================================
    ����״̬�������ս������(main.cpp�е��ý��)
    ========================================================================================================================
    */
    bool flag = false; // Ĭ������״̬�������ܽ���
    for (int i = 0; i < WordAnalyse_Results.size(); i++)
    {
        if (WordAnalyse_Results[i].ID != -1)
        {
            flag = true;
            return WordAnalyse_Results[i];
        }
    }
    // ��δ�ܽ���
    if (!flag)
    {
        return WordAnalyse_Results[0];
    }
}
