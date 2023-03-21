#include "texture.hpp"

Texture* r_create_texture(const char *filepath) {
    Texture *t = (Texture*)malloc(sizeof(Texture));

    unsigned char *data = stbi_load(filepath, &t->width, &t->height, &t->num_channels, 0);

    if(data) {
        glGenTextures(1, &t->_tex);
        glBindTexture(GL_TEXTURE_2D, t->_tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t->width, t->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {    
        fprintf(stderr, "Failed to load texture at: %s\n", filepath);
        exit(EXIT_FAILURE);
    }
    stbi_image_free(data);

    return t;
}