//
// Created by rmamin1337 on 12.11.2024.
//

#include "Camera.h"

#include <glm/ext.hpp>

#include "../window/Window.h"

Camera::Camera(const vec3 position, const float fov)
    : position(position), fov(fov), rotationMatrix(1.0f) {
    updateVectors();
}

void Camera::updateVectors() {
    front = vec3(rotationMatrix * vec4(0, 0, -1, 1));
    right = vec3(rotationMatrix * vec4(1, 0, 0, 1));
    up = vec3(rotationMatrix * vec4(0, 1, 0, 1));
}

void Camera::rotate(const float x, const float y, const float z) {
    rotationMatrix = glm::rotate(rotationMatrix, z, vec3(0, 0, 1));
    rotationMatrix = glm::rotate(rotationMatrix, y, vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, x, vec3(1, 0, 0));
    updateVectors();
}

mat4 Camera::getProjectionMatrix() const {
    const float aspect =
        static_cast<float>(Window::width) / static_cast<float>(Window::height);
    // Specify field of view, aspect ratio, and depth range.
    return perspective(fov, aspect, 0.1f, 100.0f);
}

mat4 Camera::getViewMatrix() const {
    // Specify the camera position, observation point and up direction.
    return lookAt(position, position + front, up);
}
