#include "relation.h"

Relation::Relation() {}

Relation::Relation(int state, char ch) {
	state = state;
	ch = ch;
}

/**
    map-key 使用自定义对象，需要重新规定map内部排序方法
*/
bool Relation::operator < (const Relation& r) const {
	if (this->ch == r.ch) {
		return (this->ch + this->state) < (r.ch + r.state);
	}
	else {
		return this->ch < r.ch;
	}
}

