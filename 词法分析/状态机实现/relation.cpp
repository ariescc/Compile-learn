#include "relation.h"

Relation::Relation() {}

Relation::Relation(int state, char ch) {
    state = state;
    ch = ch;
}

bool Relation::operator < (const Relation& r) const {
    if(this -> ch == r.ch) {
        return (this -> ch + this -> state) < (r.ch + r.state);
    }
    else {
        return this -> ch < r.ch;
    }
}