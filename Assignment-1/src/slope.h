#include "main.h"

#ifndef SLOPEBALLS_H
#define SLOPEBALLS_H


class Slope {
public:
    Slope() {}
    Slope(float x, float y, color_t color,double rad,double spd);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double accY;
    double speed;
    double speedY;
    double r;

    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // SLOPEBALLS_H
