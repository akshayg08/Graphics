#ifndef HEART_H
#define HEART_H

#include "main.h"

class Heart
{
public:
    Heart() {}
    Heart(double x, double y);
    void draw(glm::mat4 VP);
private:
    VAO* object;
    glm::vec3 position;
};

#endif // HEART_H
