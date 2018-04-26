#include <string>

#define LETTER_NUM 26
#define DIGIT_NUM 10

class Relation {
    public:
        int state;
        char ch;
        Relation();
        Relation(int state, char ch);
        bool operator < (const Relation& r) const;
};