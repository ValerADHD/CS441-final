#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#ifndef SHADER_H
#define SHADER_H

GLuint r_create_shader_program(char const* vertexShaderFilepath, char const* fragmentShaderFilepath);

#endif