//
// Created by rmamin1337 on 12.11.2024.
//

#include "Texture.h"

#include <GL/glew.h>

Texture::Texture(const unsigned int id, const int width, const int height)
    : id(id), width(width), height(height) {
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}