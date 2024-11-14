//
// Created by rmamin1337 on 12.11.2024.
//

#include "CubeRenderer.h"

// Vertex size: 3 coordinates, 2 UVs, 1 lighting
#define VERTEX_SIZE (3 + 2 + 1)

#define DIV_ROUND_DOWN(DIVIDEND, DIVISOR) (((DIVIDEND) < 0) ? ((DIVIDEND) / (DIVISOR) - 1) : ((DIVIDEND) / (DIVISOR)))
#define LOCAL_NEG(X_COORDINATE, SIZE) (((X_COORDINATE) < 0) ? ((SIZE) + (X_COORDINATE)) : (X_COORDINATE))
#define LOCAL(X_COORDINATE, SIZE) ((X_COORDINATE) >= (SIZE) ? ((X_COORDINATE) - (SIZE)) : LOCAL_NEG(X_COORDINATE, SIZE))
#define IS_CHUNK(X, Y, Z) (GET_CHUNK(X, Y, Z) != nullptr)
#define GET_CHUNK(X, Y, Z) (chunks[((DIV_ROUND_DOWN(Y, CHUNK_H)+1) * 3 + DIV_ROUND_DOWN(Z, CHUNK_D) + 1) * 3 + DIV_ROUND_DOWN(X, CHUNK_W) + 1])

#define GET_CUBE(X, Y, Z) (GET_CHUNK(X, Y, Z)->cubes[(LOCAL(Y, CHUNK_H) * CHUNK_D + LOCAL(Z, CHUNK_D)) * CHUNK_W + LOCAL(X, CHUNK_W)])
#define IS_BLOCKED(X,Y,Z) ((!IS_CHUNK(X, Y, Z)) || GET_CUBE(X, Y, Z).id)

#define VERTEX(INDEX, X, Y, Z, U, V, L) buffer[INDEX + 0] = (X);\
buffer[INDEX + 1] = (Y);\
buffer[INDEX + 2] = (Z);\
buffer[INDEX + 3] = (U);\
buffer[INDEX + 4] = (V);\
buffer[INDEX + 5] = (L);\
INDEX += VERTEX_SIZE;

inline int chunk_attrs[] = {3, 2, 1, 0};

CubeRenderer::CubeRenderer(const size_t capacity) : capacity(capacity) {
    buffer = new float[capacity * VERTEX_SIZE * 6];
}

CubeRenderer::~CubeRenderer() {
    delete[] buffer;
}

Mesh *CubeRenderer::render(const Chunk *chunk, const Chunk **chunks) const {
    size_t index = 0;
    for (int y = 0; y < CHUNK_H; y++) {
        for (int z = 0; z < CHUNK_D; z++) {
            for (int x = 0; x < CHUNK_W; x++) {
                const auto [id] = chunk->cubes[(y * CHUNK_D + z) * CHUNK_W + x];

                if (!id) {
                    continue;  // Skip empty blocks
                }

                float lightIntensity;
                constexpr float textureAtlasCellSize = 1.0f / 16.0f;
                const float textureCoordU = (id % 16) * textureAtlasCellSize;
                const float textureCoordV =
                    1 - ((1 + id / 16) * textureAtlasCellSize);

                if (!IS_BLOCKED(x, y + 1, z)) {
                    lightIntensity = 1.0f;
                    VERTEX(
                        index,
                        x - 0.5f,
                        y + 0.5f,
                        z - 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x - 0.5f,
                        y + 0.5f,
                        z + 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y + 0.5f,
                        z + 0.5f,
                        textureCoordU,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );

                    VERTEX(
                        index,
                        x - 0.5f,
                        y + 0.5f,
                        z - 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y + 0.5f,
                        z + 0.5f,
                        textureCoordU,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y + 0.5f,
                        z - 0.5f,
                        textureCoordU,
                        textureCoordV,
                        lightIntensity
                    );
                }
                if (!IS_BLOCKED(x, y - 1, z)) {
                    lightIntensity = 0.75f;
                    VERTEX(
                        index,
                        x - 0.5f,
                        y - 0.5f,
                        z - 0.5f,
                        textureCoordU,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y - 0.5f,
                        z + 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x - 0.5f,
                        y - 0.5f,
                        z + 0.5f,
                        textureCoordU,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );

                    VERTEX(
                        index,
                        x - 0.5f,
                        y - 0.5f,
                        z - 0.5f,
                        textureCoordU,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y - 0.5f,
                        z - 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y - 0.5f,
                        z + 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                }

                if (!IS_BLOCKED(x + 1, y, z)) {
                    lightIntensity = 0.95f;
                    VERTEX(
                        index,
                        x + 0.5f,
                        y - 0.5f,
                        z - 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y + 0.5f,
                        z - 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y + 0.5f,
                        z + 0.5f,
                        textureCoordU,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );

                    VERTEX(
                        index,
                        x + 0.5f,
                        y - 0.5f,
                        z - 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y + 0.5f,
                        z + 0.5f,
                        textureCoordU,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y - 0.5f,
                        z + 0.5f,
                        textureCoordU,
                        textureCoordV,
                        lightIntensity
                    );
                }
                if (!IS_BLOCKED(x - 1, y, z)) {
                    lightIntensity = 0.85f;
                    VERTEX(
                        index,
                        x - 0.5f,
                        y - 0.5f,
                        z - 0.5f,
                        textureCoordU,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x - 0.5f,
                        y + 0.5f,
                        z + 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x - 0.5f,
                        y + 0.5f,
                        z - 0.5f,
                        textureCoordU,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );

                    VERTEX(
                        index,
                        x - 0.5f,
                        y - 0.5f,
                        z - 0.5f,
                        textureCoordU,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x - 0.5f,
                        y - 0.5f,
                        z + 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x - 0.5f,
                        y + 0.5f,
                        z + 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                }

                if (!IS_BLOCKED(x, y, z + 1)) {
                    lightIntensity = 0.9f;
                    VERTEX(
                        index,
                        x - 0.5f,
                        y - 0.5f,
                        z + 0.5f,
                        textureCoordU,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y + 0.5f,
                        z + 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x - 0.5f,
                        y + 0.5f,
                        z + 0.5f,
                        textureCoordU,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );

                    VERTEX(
                        index,
                        x - 0.5f,
                        y - 0.5f,
                        z + 0.5f,
                        textureCoordU,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y - 0.5f,
                        z + 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y + 0.5f,
                        z + 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                }
                if (!IS_BLOCKED(x, y, z - 1)) {
                    lightIntensity = 0.8f;
                    VERTEX(
                        index,
                        x - 0.5f,
                        y - 0.5f,
                        z - 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x - 0.5f,
                        y + 0.5f,
                        z - 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y + 0.5f,
                        z - 0.5f,
                        textureCoordU,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );

                    VERTEX(
                        index,
                        x - 0.5f,
                        y - 0.5f,
                        z - 0.5f,
                        textureCoordU + textureAtlasCellSize,
                        textureCoordV,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y + 0.5f,
                        z - 0.5f,
                        textureCoordU,
                        textureCoordV + textureAtlasCellSize,
                        lightIntensity
                    );
                    VERTEX(
                        index,
                        x + 0.5f,
                        y - 0.5f,
                        z - 0.5f,
                        textureCoordU,
                        textureCoordV,
                        lightIntensity
                    );
                }
            }
        }
    }
    return new Mesh(buffer, index / VERTEX_SIZE, chunk_attrs);
}