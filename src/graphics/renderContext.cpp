#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <stdio.h>
#include <stdlib.h>

#include "renderContext.hpp"

void r_set_active_shader_program(RenderContext *rc, GLuint prog) {
    rc->active_program = prog;
    glUseProgram(prog);

    GLuint view_uniform = glGetUniformLocation(prog, "view");
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, &rc->view_matrix[0][0]);
    GLuint projection_uniform = glGetUniformLocation(prog, "projection");
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, &rc->projection_matrix[0][0]);
}

void r_set_view_matrix(RenderContext *rc, glm::mat4 mat) {
    rc->view_matrix = mat;
    GLuint view_uniform = glGetUniformLocation(rc->active_program, "view");
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, &rc->view_matrix[0][0]);
}