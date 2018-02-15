#include "slope.h"
#include "main.h"

Slope::Slope(float x, float y, color_t color,double rad,double spd ) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = spd;//((double)rand()/RAND_MAX)*0.05;
//    speedY = 0.3;
//    accY = -0.1;
    static GLfloat g_vertex_buffer_data[9018];
     int p=0;
 //    float pi=3.14;
//     double r = ((double) rand() / (RAND_MAX)) + 1;
     this->r = rad;
     for(int i=0;i<1000;i++)
     {
         double a = (2*i+1)*(double)M_PI/1000;
         for(int j=0;j<3;j++)
             g_vertex_buffer_data[p++]=0.0f;
         g_vertex_buffer_data[p++]=this->r*(float)cos(a);
         g_vertex_buffer_data[p++]=this->r*(float)sin(a);
         g_vertex_buffer_data[p++]=0.0f;
         a+=(double)M_PI/500;
         g_vertex_buffer_data[p++]=this->r*(float)cos(a);
         g_vertex_buffer_data[p++]=this->r*(float)sin(a);
         g_vertex_buffer_data[p++]=0.0f;
     }
     g_vertex_buffer_data[p++]=(-r*sqrt(2)-0.1/sqrt(2));
     g_vertex_buffer_data[p++]=0.1/sqrt(2);
     g_vertex_buffer_data[p++]=0.0f;
     g_vertex_buffer_data[p++]=-0.1/sqrt(2);
     g_vertex_buffer_data[p++]=(r*sqrt(2)+0.1/sqrt(2));
     g_vertex_buffer_data[p++]=0.0f;
     g_vertex_buffer_data[p++]=0;
     g_vertex_buffer_data[p++]=r*sqrt(2);
     g_vertex_buffer_data[p++]=0.0f;
     g_vertex_buffer_data[p++]=0;
     g_vertex_buffer_data[p++]=r*sqrt(2);
     g_vertex_buffer_data[p++]=0.0f;
     g_vertex_buffer_data[p++]=-r*sqrt(2);
     g_vertex_buffer_data[p++]=0;
     g_vertex_buffer_data[p++]=0.0f;
     g_vertex_buffer_data[p++]=(-r*sqrt(2)-0.1/sqrt(2));
     g_vertex_buffer_data[p++]=0.1/sqrt(2);
     g_vertex_buffer_data[p++]=0.0f;

    this->object = create3DObject(GL_TRIANGLES, 9018, g_vertex_buffer_data, color, GL_FILL);
}

void Slope::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Slope::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Slope::tick() {
    this->position.x += this->speed;
}

bounding_box_t Slope::bounding_box() {
    float x = this->position.x, y = this->position.y;
    float ri = this->r;
    bounding_box_t bbox = { x, y, ri };
    return bbox;
}
