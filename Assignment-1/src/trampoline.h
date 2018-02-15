#include "main.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H


class Trampoline {
public:
    Trampoline() {}
    Trampoline(float radius, float x, float y, float length, float breadth, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    float radius;
    float length;
    float breadth;
    void set_position(float x, float y);
    // void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // TRAMPOLINE_H
