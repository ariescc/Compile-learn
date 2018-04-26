#include "relation.h"

Relation::Relation() {}

Relation::Relation(int state, char ch) {
    state = state;
    ch = ch;
}

bool Relation::operator < (const Relation& r) const {
    return this -> state < r.state;
}