#ifndef MODEL_H
#define MODEL_H

#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>

typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
} Vertex;

typedef struct {
    Vertex *vertices;
    int num_vertices;
    GLuint *indices;
    int num_indices;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
} Model;

Model* r_load_model(const char *path);
void r_delete_model(Model *m);

#endif