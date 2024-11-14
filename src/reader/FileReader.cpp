//
// Created by rmamin1337 on 12.11.2024.
//

#include "FileReader.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string FileReader::readFile(const std::string& fileName) {
    try {
        std::ifstream file(fileName);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + fileName);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        file.close();
        return buffer.str();
    } catch (std::ifstream::failure& e) {
        throw std::runtime_error(
            "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " + fileName
        );
    }
}