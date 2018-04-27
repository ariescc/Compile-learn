#pragma once

class Relation {
public:
	int state;
	char ch;
	Relation();
	Relation(int state, char ch);
	bool operator < (const Relation& r) const;
};
