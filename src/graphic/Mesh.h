//
// Created by rmamin1337 on 12.11.2024.
//

#ifndef MESH_H
#define MESH_H

#include <cstddef>

class Mesh {
    unsigned int vertexArrayObjectId = 0;
    unsigned int vertexBufferObjectId = 0;

    size_t vertexCount;     // Number of vertices.
    int *vertexAttributes;  // Vertex attributes.

    static void checkOpenGLError();
public:
    Mesh(const float *vertexBuffer, size_t vertexCount, int *vertexAttributes);

    ~Mesh();

    void draw(unsigned int primitive) const;
};

#endif  // MESH_H
