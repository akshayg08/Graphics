#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float r, float vel, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    xspeed = vel;
    gg = 0.1f;

    static GLfloat vertex_buffer_data[360*9];
    float pi=M_PI*2;
    int n=360;
    rad =r;
    float xs=r , ys=0 , c=cos(pi/n) , s=sin(pi/n);
    /*
    = {
        -0.2, -0.2, 0, // vertex 1
        0.2,  -0.2, 0, // vertex 2
        0.2,  0.2, 0, // vertex 3

        0.2,  0.2, 0, // vertex 3
        -0.2, 0.2, 0, // vertex 4
        -0.2, -0.2, 0 // vertex 1
    };
    */
    for(int i=0;i<n*9;)
    {
        float x1 = xs*c - ys*s;
        float y1 = xs*s + ys*c;
        vertex_buffer_data[i++]=0;
        vertex_buffer_data[i++]=0;
        vertex_buffer_data[i++]=0.0f;
        vertex_buffer_data[i++]=xs;
        vertex_buffer_data[i++]=ys;
        vertex_buffer_data[i++]=0.0f;
        vertex_buffer_data[i++]=x1;
        vertex_buffer_data[i++]=y1;
        vertex_buffer_data[i++]=0.0f;
        xs=x1,ys=y1;
    }

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::set_speedx(float x,int y)
{
    this->xspeed = x;
}

void Ball::set_speedy(float x,int y)
{
    this->yspeed = x;
}

void Ball::tick() {
    this->position.x += xspeed;
    //if(this->position.y-xspeed<=4 && this->position.y-xspeed>=-4)
        this->position.y -= yspeed;
}

void Ball::left()
{
    if(this->position.x-0.1<=4 && this->position.x-0.1>=-4)
        this->position.x -= 0.15f;
}

void Ball::right()
{
    if(this->position.x+0.1<=4 && this->position.x+0.1>=-4)
        this->position.x += 0.15f;
}

void Ball::up(float x)
{
    //if(this->position.y+0.2<=4 && this->position.y+0.2>=-4)
        this->position.y += x;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float ri = this->rad;
    bounding_box_t bbox = { x, y, ri , this->xspeed , this->yspeed, 0.4, 0.4};
    return bbox;
}
