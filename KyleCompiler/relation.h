/**
    定义起始状态与触发字符的绑定关系，即T[]的下标
*/

#pragma once

class Relation {
public:
	int state;
	char ch;
	Relation();
	Relation(int state, char ch);
	bool operator < (const Relation& r) const;
};
