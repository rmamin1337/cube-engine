//
// Created by rmamin1337 on 12.11.2024.
//

#ifndef CHUNK_H

#define CHUNK_W 16
#define CHUNK_H 16
#define CHUNK_D 16
#define CHUNK_VOL (CHUNK_W * CHUNK_H * CHUNK_D)

#include "Chunk.h"
#include "Cube.h"

class Chunk {
public:
    int x, y, z;
    Cube *cubes {};
    mutable bool modified = true;

    Chunk(int x, int y, int z);

    ~Chunk();
};

#endif  // CHUNK_H
