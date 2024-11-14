//
// Created by rmamin1337 on 12.11.2024.
//

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
public:
    unsigned int id;
    int width;
    int height;

    static Texture* fromLoader(
        const unsigned int id, const int width, const int height
    ) {
        return new Texture(id, width, height);
    }

    Texture(unsigned int id, int width, int height);

    ~Texture();

    void bind() const;
};

#endif  // TEXTURE_H
