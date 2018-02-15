#include "magnet.h"
#include "main.h"
#include "math.h"

Magnet::Magnet(float x, float y, color_t color, float rotation) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = rotation;
    alive = 0;

    static const GLfloat vertex_buffer_data[] = {
        0, 0, 0, // vertex 1
        0,  1, 0, // vertex 2
        0.2,  1, 0, // vertex 3

        0.2, 1, 0, // vertex 1
        0.2,  0, 0, // vertex 2
        0,  0, 0, // vertex 3

        0.2,  1, 0, // vertex 3
        1.2, 1, 0, // vertex 4
        0.2, 0.8, 0, // vertex 1

        0.2,  0.8, 0, // vertex 3
        1.2, 1, 0, // vertex 4
        1.2, 0.8, 0, // vertex 1

        0.2,  0, 0, // vertex 3
        1.2, 0, 0, // vertex 4
        1.2, 0.2, 0, // vertex 1

        1.2,  0.2, 0, // vertex 3
        0.2, 0.2, 0, // vertex 4
        0.2, 0, 0 // vertex 1
    };

    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}