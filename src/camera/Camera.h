//
// Created by rmamin1337 on 12.11.2024.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
using namespace glm;

class Camera {
public:
    // Camera position in space.
    vec3 position;

    // Camera field of view.
    float fov;

    // Camera Guide Vectors.
    vec3 front {};  // Forward vector.
    vec3 up {};     // Up vector.
    vec3 right {};  // Right vector.

    // Rotation matrix to store camera orientation.
    mat4 rotationMatrix;

    Camera(vec3 position, float fov);

    // Method for getting projection matrix.
    [[nodiscard]] mat4 getProjectionMatrix() const;

    // // Method for getting a matrix of the form.
    [[nodiscard]] mat4 getViewMatrix() const;

    // Method to rotate the camera to specified angles (x, y, z).
    void rotate(float x, float y, float z);
private:
    // Update direction vectors (front, right, up) based on current rotation
    // matrix.
    void updateVectors();
};

#endif  // CAMERA_H
