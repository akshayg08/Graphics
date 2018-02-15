#include "main.h"

#ifndef SEMI_H
#define SEMI_H


class Semi {
public:
    Semi() {}
    Semi(float x, float y, float r,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    //bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // SEMI_H
