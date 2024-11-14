//
// Created by rmamin1337 on 12.11.2024.
//

#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    unsigned int id;

    static Shader* fromLoader(const unsigned int id) {
        return new Shader(id);
    }

    explicit Shader(unsigned int shaderId);

    ~Shader();

    void bind() const;

    void setUniformMatrix(const std::string& matrixName, glm::mat4 matrix)
        const;
};

#endif  // SHADER_H
