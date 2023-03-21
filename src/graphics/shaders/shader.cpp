#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "shader.hpp"

GLuint r_create_shader_program(char const* vertex_shader_filepath, char const* fragment_shader_filepath) {
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    FILE* f = fopen(vertex_shader_filepath, "r");
    char *vertex_shader_code;
    if (f) {
        int len;
        fseek(f, 0, SEEK_END);
        len = ftell(f);
        fseek(f, 0, SEEK_SET);

        vertex_shader_code = (char*)malloc(len + 1);
        fread(vertex_shader_code, len, sizeof(char), f);
        vertex_shader_code[len] = EOF;
        fclose(f);
    } else {
        fprintf(stderr, "Unable to open vertex shader at: %s\n", vertex_shader_filepath);
        exit(EXIT_FAILURE);
    }

    f = fopen(fragment_shader_filepath, "r");
    char *fragment_shader_code;
    if (f) {
        int len;
        fseek(f, 0, SEEK_END);
        len = ftell(f);
        fseek(f, 0, SEEK_SET);

        fragment_shader_code = (char*)malloc(len + 1);
        fread(fragment_shader_code, len, sizeof(char), f);
        fragment_shader_code[len] = EOF;
        fclose(f);
    } else {
        fprintf(stderr, "Unable to open fragment shader at: %s\n", fragment_shader_filepath);
        exit(EXIT_FAILURE);
    }

    GLint result = 0;
    int info_log_length = 0;

    fprintf(stderr, "Compiling shader : %s\n", vertex_shader_filepath);
    const char *vertex_shader_code_ptr = vertex_shader_code;
    glShaderSource(vertex_shader_id, 1, &vertex_shader_code_ptr, NULL);
    glCompileShader(vertex_shader_id);

    //get results of shader compilation
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if(info_log_length > 0) {
        char* info_log = (char*)malloc(info_log_length + 1);
        glGetShaderInfoLog(vertex_shader_id, info_log_length, NULL, info_log);
        fprintf(stderr, "%s\n", info_log);
        fprintf(stderr, "Shader: \n%s\n", vertex_shader_code);
        free(info_log);
    }

    fprintf(stderr, "Compiling shader : %s\n", fragment_shader_filepath);
    const char *fragment_shader_code_ptr = fragment_shader_code;
    glShaderSource(fragment_shader_id, 1, &fragment_shader_code_ptr, NULL);
    glCompileShader(fragment_shader_id);

    //get results of shader compilation
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if(info_log_length > 0) {
        char* info_log = (char*)malloc(info_log_length + 1);
        glGetShaderInfoLog(fragment_shader_id, info_log_length, NULL, info_log);
        fprintf(stderr, "%s\n", info_log);
        fprintf(stderr, "Shader: \n%s\n", fragment_shader_code);
        free(info_log);
    }

    free(vertex_shader_code);
    free(fragment_shader_code);

    fprintf(stderr, "Linking program\n");
    GLuint program_id = 0;
    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    //check program for errors
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if(info_log_length > 0) {
        char* info_log = (char*)malloc(info_log_length + 1);
        glGetProgramInfoLog(program_id, info_log_length, NULL, info_log);
        fprintf(stderr, "%s\n", info_log);
    }

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}
