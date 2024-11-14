//
// Created by rmamin1337 on 12.11.2024.
//

#include "Mesh.h"

#include <GL/glew.h>

#include <cstddef>
#include <iostream>

Mesh::Mesh(
    const float *vertexBuffer, const size_t vertexCount, int *vertexAttributes
)
    : vertexCount(vertexCount), vertexAttributes(vertexAttributes) {
    int vertexSize = 0;
    for (int i = 0; vertexAttributes[i]; i++) {
        vertexSize += vertexAttributes[i];
    }

    glGenVertexArrays(1, &vertexArrayObjectId);
    glGenBuffers(1, &vertexBufferObjectId);

    glBindVertexArray(vertexArrayObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * vertexSize * vertexCount,
        vertexBuffer,
        GL_STATIC_DRAW
    );

    checkOpenGLError();

    // attributes
    int offset = 0;
    for (int i = 0; vertexAttributes[i]; i++) {
        const int attributeSize = vertexAttributes[i];
        glVertexAttribPointer(
            i,
            attributeSize,
            GL_FLOAT,
            GL_FALSE,
            vertexSize * sizeof(float),
            reinterpret_cast<GLvoid *>(offset * sizeof(float))
        );
        glEnableVertexAttribArray(i);
        offset += attributeSize;
    }

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vertexArrayObjectId);
    glDeleteBuffers(1, &vertexBufferObjectId);
}

void Mesh::draw(const unsigned int primitive) const {
    glBindVertexArray(vertexArrayObjectId);
    glDrawArrays(primitive, 0, vertexCount);
    glBindVertexArray(0);
}

void Mesh::checkOpenGLError() {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error in Mesh"
                  << ": " << error << std::endl;
    }
}