//
// Created by rmamin1337 on 12.11.2024.
//

#ifndef CUBERENDERER_H
#define CUBERENDERER_H

#include "../cube/Chunk.h"
#include "Mesh.h"

class CubeRenderer {
    float *buffer;
    size_t capacity;
public:
    explicit CubeRenderer(size_t capacity);

    ~CubeRenderer();

    Mesh *render(const Chunk *chunk, const Chunk **chunks) const;
};

#endif  // CUBERENDERER_H
