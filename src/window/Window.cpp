//
// Created by rmamin1337 on 11.11.2024.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"

GLFWwindow *Window::instance = nullptr;
bool Window::isShouldClose = false;
int Window::width = 0;
int Window::height = 0;

int Window::initialize(const WindowProperty &window_property) {
    glfwInit();

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    instance = glfwCreateWindow(
        window_property.width,
        window_property.height,
        window_property.title.c_str(),
        nullptr,
        nullptr
    );
    width = window_property.width;
    height = window_property.height;

    if (instance == nullptr) {
        std::cerr << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(instance);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW." << std::endl;
        return -1;
    }

    glViewport(0, 0, window_property.width, window_property.height);

    if (window_property.isVsyncEnable) {
        glfwSwapInterval(1);
    }

    glfwShowWindow(instance);

    return 0;
}

void Window::update() {
    glfwSwapBuffers(instance);
}

void Window::destroy() {
    glfwDestroyWindow(instance);
    glfwTerminate();
}

bool Window::getShouldClose() {
    return isShouldClose;
}

void Window::setShouldClose(const bool isShouldClose) {
    Window::isShouldClose = isShouldClose;
}

void Window::setCursorMode(const int cursorMode) {
    glfwSetInputMode(instance, GLFW_CURSOR, cursorMode);
}

void Window::clear(const float red, const float green, const float blue, const float alpha) {
    glClearColor(red, green, blue, alpha);
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
