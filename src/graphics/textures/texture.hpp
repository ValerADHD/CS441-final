#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include "../../include/stb_image.h"

#include <GL/glew.h>

typedef struct {
    int width;
    int height;
    int num_channels;

    GLuint _tex;
} Texture;

Texture* r_create_texture(const char *filepath);

#endif