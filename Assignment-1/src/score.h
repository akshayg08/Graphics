#ifndef SCORE_H
#define SCORE_H

#include "digit.h"

class Score
{
public:
    Score();
    void draw(glm::mat4 VP);
    void update(int score);
    void add1(int d =1);
    void add2(int d = 2);
    void subtract(int d = 50);
private:
    int score, digslen;
    Digit digs[50];
};

#endif // SCORE_H
