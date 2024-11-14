//
// Created by rmamin1337 on 12.11.2024.
//

#include "Shader.h"

#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const unsigned int shaderId) : id(shaderId) {
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::bind() const {
    glUseProgram(id);
}

void Shader::setUniformMatrix(const std::string& matrixName, glm::mat4 matrix)
    const {
    const GLuint transformLocation =
        glGetUniformLocation(id, matrixName.c_str());
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(matrix));
}
