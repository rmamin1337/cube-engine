//
// Created by rmamin1337 on 12.11.2024.
//

#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <GL/glew.h>

#include <string>

#include "../graphic/Shader.h"
#include "ShaderLoader.h"

class ShaderLoader {
public:
    // Method for loading and compiling a single shader (vertex or fragment).
    static GLuint loadShader(GLenum shaderType, const std::string &shaderCode);

    // Method for creating and linking a shader program.
    static Shader *loadShaderProgram(
        const std::string &vertexShaderCode,
        const std::string &fragmentShaderCode
    );
private:
    // Method for checking shader compilation errors.
    static bool checkCompileErrors(GLuint shaderId, const std::string &type);

    // Method for checking program linking errors.
    static bool checkLinkErrors(GLuint shaderProgramId);
};

#endif  // SHADERLOADER_H
