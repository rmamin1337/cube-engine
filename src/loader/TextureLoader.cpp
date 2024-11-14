//
// Created by rmamin1337 on 12.11.2024.
//

#define STB_IMAGE_IMPLEMENTATION

#include "TextureLoader.h"

#include <GL/glew.h>

#include <stdexcept>

#include "../include/stb_image.h"

Texture *TextureLoader::loadTexture(const std::string &filePath) {
    // Enable vertical image flip.
    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;

    unsigned char *image =
        stbi_load(filePath.c_str(), &width, &height, &channels, 4);
    if (!image) {
        throw std::runtime_error("Failed to load texture file: " + filePath);
    }

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Setting texture parameters for minimum and maximum filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Loading an Image into a Texture and Creating a Mipmap.
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        image
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image);

    return Texture::fromLoader(textureId, width, height);
}
