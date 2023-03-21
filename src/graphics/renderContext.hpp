#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

typedef struct {
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix;

    GLuint active_program;
} RenderContext;

void r_set_active_shader_program(RenderContext *rc, GLuint prog);
void r_set_view_matrix(RenderContext *rc, glm::mat4 mat);

#endif