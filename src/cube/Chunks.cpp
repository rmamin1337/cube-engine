#include "Chunks.h"

#include <cmath>
#include <glm/glm.hpp>

#include "Chunk.h"
#include "Cube.h"

Chunks::Chunks(
    const unsigned int width,
    const unsigned int height,
    const unsigned int depth
)
    : width(width), height(height), depth(depth) {
    totalChunks = width * height * depth;
    chunks = new Chunk *[totalChunks];

    int currentIndex = 0;
    // Fill an array of chunks, initializing each chunk with its
    // coordinates.
    for (int y = 0; y < height; y++) {
        for (int z = 0; z < depth; z++) {
            for (int x = 0; x < width; x++, currentIndex++) {
                chunks[currentIndex] = new Chunk(x, y, z);
            }
        }
    }
}

Chunks::~Chunks() {
    for (int i = 0; i < totalChunks; i++) {
        delete chunks[i];
    }
    delete[] chunks;
}

// Method for getting a pointer to a cube by world coordinates x, y, z.
[[nodiscard]] Cube *Chunks::getCubeByCoordinates(
    const int x, const int y, const int z
) const {
    int chunkX = x / CHUNK_W;
    int chunkY = y / CHUNK_H;
    int chunkZ = z / CHUNK_D;

    // Check that the coordinates are within the chunk array.
    if (x < 0) {
        chunkX--;
    }
    if (y < 0) {
        chunkY--;
    }
    if (z < 0) {
        chunkZ--;
    }

    if (chunkX < 0 || chunkY < 0 || chunkZ < 0 || chunkX >= width ||
        chunkY >= height || chunkZ >= depth) {
        return nullptr;
    }

    // Get a pointer to the chunk and calculate local coordinates inside it.
    const Chunk *targetChunk =
        chunks[(chunkY * depth + chunkZ) * width + chunkX];
    const int localX = x - chunkX * CHUNK_W;
    const int localY = y - chunkY * CHUNK_H;
    const int localZ = z - chunkZ * CHUNK_D;

    return &targetChunk->cubes[(localY * CHUNK_D + localZ) * CHUNK_W + localX];
}

// Method for getting a pointer to a chunk by world coordinates x, y, z.
[[nodiscard]] Chunk *Chunks::getChunkByCoordinates(
    const int x, const int y, const int z
) const {
    if (x < 0 || y < 0 || z < 0 || x >= width || y >= height || z >= depth) {
        return nullptr;
    }
    return chunks[(y * depth + z) * width + x];
}

// Set the cube ID and mark the chunk as changed.
void Chunks::setCube(const int x, const int y, const int z, const int cubeId)
    const {
    int chunkX = x / CHUNK_W;
    int chunkY = y / CHUNK_H;
    int chunkZ = z / CHUNK_D;

    // Check that the coordinates are within the chunk array.
    if (x < 0) {
        chunkX--;
    }
    if (y < 0) {
        chunkY--;
    }
    if (z < 0) {
        chunkZ--;
    }

    if (chunkX < 0 || chunkY < 0 || chunkZ < 0 || chunkX >= width ||
        chunkY >= height || chunkZ >= depth) {
        return;
    }

    // Get a pointer to the chunk and calculate local coordinates inside it.
    const Chunk *targetChunk =
        chunks[(chunkY * depth + chunkZ) * width + chunkX];
    const int localX = x - chunkX * CHUNK_W;
    const int localY = y - chunkY * CHUNK_H;
    const int localZ = z - chunkZ * CHUNK_D;

    targetChunk->cubes[(localY * CHUNK_D + localZ) * CHUNK_W + localX].id =
        cubeId;
    targetChunk->modified = true;

    // Check and mark border chunks as changed.
    if (localX == 0 &&
        ((targetChunk = getChunkByCoordinates(chunkX - 1, chunkY, chunkZ))))
        targetChunk->modified = true;
    if (localY == 0 &&
        ((targetChunk = getChunkByCoordinates(chunkX, chunkY - 1, chunkZ))))
        targetChunk->modified = true;
    if (localZ == 0 &&
        ((targetChunk = getChunkByCoordinates(chunkX, chunkY, chunkZ - 1))))
        targetChunk->modified = true;

    if (localX == CHUNK_W - 1 &&
        ((targetChunk = getChunkByCoordinates(chunkX + 1, chunkY, chunkZ))))
        targetChunk->modified = true;
    if (localY == CHUNK_H - 1 &&
        ((targetChunk = getChunkByCoordinates(chunkX, chunkY + 1, chunkZ))))
        targetChunk->modified = true;
    if (localZ == CHUNK_D - 1 &&
        ((targetChunk = getChunkByCoordinates(chunkX, chunkY, chunkZ + 1))))
        targetChunk->modified = true;
}

// Ray tracing method.
// hitPosition - coordinates of the intersection point.
// hitNormal - the normal of the surface on which the beam “hit” (in which
// plane the intersection occurred).
Cube *Chunks::rayCast(
    const vec3 origin,
    const vec3 direction,
    const float maxDistance,
    vec3 &hitPosition,
    vec3 &hitNormal,
    vec3 &cubeCoords
) const {
    // Beam starting point coordinates.
    const float positionX = origin.x;
    const float positionY = origin.y;
    const float positionZ = origin.z;

    const float directionX = direction.x;
    const float directionY = direction.y;
    const float directionZ = direction.z;

    // Coordinates of the current cube when tracing.
    int cubeX = static_cast<int>(std::floor(positionX));
    int cubeY = static_cast<int>(std::floor(positionY));
    int cubeZ = static_cast<int>(std::floor(positionZ));

    // Steps along each axis as the beam moves.
    const float stepX = (directionX > 0.0f) ? 1.0f : -1.0f;
    const float stepY = (directionY > 0.0f) ? 1.0f : -1.0f;
    const float stepZ = (directionZ > 0.0f) ? 1.0f : -1.0f;

    constexpr float infinity = std::numeric_limits<float>::infinity();

    // Deltas to calculate the intersection on each axis.
    const float deltaX =
        (directionX == 0.0f) ? infinity : abs(1.0f / directionX);
    const float deltaY =
        (directionY == 0.0f) ? infinity : abs(1.0f / directionY);
    const float deltaZ =
        (directionZ == 0.0f) ? infinity : abs(1.0f / directionZ);

    const float distanceX =
        (stepX > 0) ? (cubeX + 1 - positionX) : (positionX - cubeX);
    const float distanceY =
        (stepY > 0) ? (cubeY + 1 - positionY) : (positionY - cubeY);
    const float distanceZ =
        (stepZ > 0) ? (cubeZ + 1 - positionZ) : (positionZ - cubeZ);

    // Intersection times for each axis.
    float maxX = (deltaX < infinity) ? deltaX * distanceX : infinity;
    float maxY = (deltaY < infinity) ? deltaY * distanceY : infinity;
    float maxZ = (deltaZ < infinity) ? deltaZ * distanceZ : infinity;

    float currentDistance = 0.0f;
    int steppedIndex = -1;
    while (currentDistance <= maxDistance) {
        if (Cube *cube = getCubeByCoordinates(cubeX, cubeY, cubeZ);
            cube == nullptr || cube->id) {
            hitPosition.x = positionX + currentDistance * deltaX;
            hitPosition.y = positionY + currentDistance * deltaY;
            hitPosition.z = positionZ + currentDistance * deltaZ;

            cubeCoords.x = cubeX;
            cubeCoords.y = cubeY;
            cubeCoords.z = cubeZ;

            hitNormal.x = hitNormal.y = hitNormal.z = 0.0f;
            if (steppedIndex == 0) {
                hitNormal.x = -stepX;
            }
            if (steppedIndex == 1) {
                hitNormal.y = -stepY;
            }
            if (steppedIndex == 2) {
                hitNormal.z = -stepZ;
            }
            return cube;
        }

        if (maxX < maxY) {
            if (maxX < maxZ) {
                cubeX += stepX;
                currentDistance = maxX;
                maxX += deltaX;
                steppedIndex = 0;
            } else {
                cubeZ += stepZ;
                currentDistance = maxZ;
                maxZ += deltaZ;
                steppedIndex = 2;
            }
        } else {
            if (maxY < maxZ) {
                cubeY += stepY;
                currentDistance = maxY;
                maxY += deltaY;
                steppedIndex = 1;
            } else {
                cubeZ += stepZ;
                currentDistance = maxZ;
                maxZ += deltaZ;
                steppedIndex = 2;
            }
        }
    }

    cubeCoords.x = cubeX;
    cubeCoords.y = cubeY;
    cubeCoords.z = cubeZ;

    hitPosition.x = positionX + currentDistance * deltaX;
    hitPosition.y = positionY + currentDistance * deltaY;
    hitPosition.z = positionZ + currentDistance * deltaZ;

    hitNormal.x = hitNormal.y = hitNormal.z = 0.0f;
    return nullptr;
}