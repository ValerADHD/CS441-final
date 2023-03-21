#include <GL/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "model.hpp"

Model* r_load_model(const char *path) {
    Model *m = (Model*)malloc(sizeof(Model));

    Assimp::Importer model_importer;

    const aiScene *scene = model_importer.ReadFile(path, 
        aiProcess_GenSmoothNormals
    );

    if(scene == NULL) {
        fprintf(stderr, "%s\n", model_importer.GetErrorString());
        exit(EXIT_FAILURE);
    }

    aiMesh *mesh = scene->mMeshes[0];
    
    m->num_vertices = mesh->mNumVertices;
    m->vertices = (Vertex*)malloc(m->num_vertices * sizeof(Vertex));

    for(int i = 0; i < mesh->mNumVertices; i++) {
        Vertex *v = &m->vertices[i];

        v->position.x = mesh->mVertices[i].x;
        v->position.y = mesh->mVertices[i].y;
        v->position.z = mesh->mVertices[i].z;
        v->normal.x = mesh->mNormals[i].x;
        v->normal.y = mesh->mNormals[i].y;
        v->normal.z = mesh->mNormals[i].z;
    }

    m->num_indices = mesh->mNumFaces * 3;
    m->indices = (GLuint*)malloc(m->num_indices * sizeof(GLuint));

    for(int i = 0; i < mesh->mNumFaces; i++) {
        m->indices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
        m->indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
        m->indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
    }

    glGenVertexArrays(1, &m->_vao);
    glBindVertexArray(m->_vao);

    glGenBuffers(1, &m->_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m->_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m->num_vertices, m->vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m->_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m->num_indices, m->indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glBindVertexArray(0);

    return m;
}

void r_delete_model(Model* m) {
    free(m->indices);
    free(m->vertices);

    glDeleteVertexArrays(1, &m->_vao);
    glDeleteBuffers(1, &m->_ebo);
    glDeleteBuffers(1, &m->_vbo);
}