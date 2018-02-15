#include "semi.h"
#include "main.h"

Semi::Semi(float x, float y, float r, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 180;
    static GLfloat vertex_buffer_data[360*9];
    float pi=M_PI*2;
    int n=180;
    //rad =r;
    float xs=r , ys=0 , c=cos(pi/360) , s=sin(pi/360);
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

void Semi::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Semi::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Semi::tick() {
    this->position.x -= speed;
    // this->position.y -= speed;
}

/*bounding_box_t Rect::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.4, 0.4 };
    return bbox;
}
*/
