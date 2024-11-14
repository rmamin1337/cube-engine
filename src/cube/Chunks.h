//
// Created by rmamin1337 on 12.11.2024.
//

#ifndef CHUNKS_H
#define CHUNKS_H

#include <glm/glm.hpp>

#include "Chunk.h"
#include "Cube.h"
using namespace glm;

class Chunks {
    unsigned int width, height, depth;
public:
    Chunk **chunks;
    size_t totalChunks;

    Chunks(unsigned int width, unsigned int height, unsigned int depth);

    ~Chunks();

    // Method for getting a pointer to a cube by world coordinates x, y, z.
    [[nodiscard]] Cube *getCubeByCoordinates(int x, int y, int z) const;

    // Method for getting a pointer to a chunk by world coordinates x, y, z.
    [[nodiscard]] Chunk *getChunkByCoordinates(int x, int y, int z) const;

    // Set the cube ID and mark the chunk as changed.
    void setCube(int x, int y, int z, int cubeId) const;

    // Ray tracing method.
    // hitPosition - coordinates of the intersection point.
    // hitNormal - the normal of the surface on which the beam “hit” (in which
    // plane the intersection occurred).
    Cube *rayCast(
        vec3 origin,
        vec3 direction,
        float maxDistance,
        vec3 &hitPosition,
        vec3 &hitNormal,
        vec3 &cubeCoords
    ) const;
};

#endif  // CHUNKS_H
