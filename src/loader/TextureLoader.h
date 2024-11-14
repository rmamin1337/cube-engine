//
// Created by rmamin1337 on 12.11.2024.
//

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <string>

#include "../graphic/Texture.h"

class TextureLoader {
public:
    static Texture* loadTexture(const std::string& filePath);
};

#endif  // TEXTURELOADER_H