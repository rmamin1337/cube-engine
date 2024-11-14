//
// Created by rmamin1337 on 12.11.2024.
//

#include "ShaderLoader.h"

#include <GL/glew.h>

#include <iostream>
#include <ostream>

#include "../graphic/Shader.h"

GLuint ShaderLoader::loadShader(
    const GLenum shaderType, const std::string &shaderCode
) {
    const GLuint shaderId = glCreateShader(shaderType);
    const char *shaderSourceCode = shaderCode.c_str();
    glShaderSource(shaderId, 1, &shaderSourceCode, nullptr);
    glCompileShader(shaderId);

    if (!checkCompileErrors(shaderId, "SHADER")) {
        glDeleteShader(shaderId);
        throw std::runtime_error("Shader compilation failed");
    }

    return shaderId;
}

Shader *ShaderLoader::loadShaderProgram(
    const std::string &vertexShaderCode, const std::string &fragmentShaderCode
) {
    const GLuint vertexShaderId =
        loadShader(GL_VERTEX_SHADER, vertexShaderCode);
    const GLuint fragmentShaderId =
        loadShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    const GLuint shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);

    if (!checkLinkErrors(shaderProgramId)) {
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
        glDeleteProgram(shaderProgramId);
        throw std::runtime_error("Shader linking failed");
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return Shader::fromLoader(shaderProgramId);
}

bool ShaderLoader::checkCompileErrors(
    const GLuint shaderId, const std::string &type
) {
    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
        std::cerr << type << " COMPILATION ERROR\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

bool ShaderLoader::checkLinkErrors(const GLuint shaderProgramId) {
    GLint success;
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(shaderProgramId, 1024, nullptr, infoLog);
        std::cerr << "PROGRAM LINKING ERROR\n" << infoLog << std::endl;
        return false;
    }
    return true;
}
