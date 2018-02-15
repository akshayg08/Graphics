#include "main.h"

#ifndef PORCUPINE_H
#define PORCUPINE_H


class Porcupine
{
public:
    Porcupine(){};
    Porcupine(float x, float y, float xmax, float xmin, float xspeed, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    double xspeed;
    float xmax;
    float xmin;
private:
    VAO *object;
};

#endif // PORCUPINE_H
