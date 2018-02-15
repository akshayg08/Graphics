#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float r, float vel,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void set_speedx(float x,int y);
    void set_speedy(float x,int y);
    void tick();
    void left();
    void right();
    void up(float x);
    double xspeed;
    double yspeed;
    double gg;
    double rad;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
