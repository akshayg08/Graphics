#include "heart.h"
#include "main.h"

Heart::Heart(double x, double y) {
    this->position = glm::vec3(x, y, 0);
    static const GLfloat vertex_buffer_data [] = {
        0, .1, 0,
        .1, .2, 0,
        .2, .1, 0,
        0, -.1, 0,
        -.2, .1, 0,
        -.1, .2, 0,
    };
    this->object = create3DObject(GL_LINE_LOOP, 6, vertex_buffer_data, COLOR_RED, GL_LINE);
}

void Heart::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    Matrices.model *=  glm::translate(position);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
