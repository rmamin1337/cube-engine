//
// Created by rmamin1337 on 12.11.2024.
//

#include "Chunk.h"

#include <cmath>

#include "Cube.h"

Chunk::Chunk(const int x, const int y, const int z) : x(x), y(y), z(z) {
    cubes = new Cube[CHUNK_VOL];

    // Генерация псевдо-ландшафта внутри чанка.
    for (int yPosition = 0; yPosition < CHUNK_H; yPosition++) {
        for (int zPosition = 0; zPosition < CHUNK_D; zPosition++) {
            for (int xPosition = 0; xPosition < CHUNK_W; xPosition++) {
                const int globalX = xPosition + this->x * CHUNK_W;
                const int globalY = yPosition + this->y * CHUNK_H;
                // int globalZ = zPosition + this->z * CHUNK_D;

                int id = globalY <= (sin(globalX * 0.1f) * 0.5f + 0.5f) * 10;
                if (globalY <= 2) {
                    id = 2;
                }

                cubes[(yPosition * CHUNK_D + zPosition) * CHUNK_W + xPosition]
                    .id = id;
            }
        }
    }
}

Chunk::~Chunk() {
    delete[] cubes;
}