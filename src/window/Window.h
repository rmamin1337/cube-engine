//
// Created by rmamin1337 on 11.11.2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

#include "../property/WindowProperty.h"

class Window {
public:
    static GLFWwindow *instance;
    static bool isShouldClose;
    static int width;
    static int height;

    static int initialize(const WindowProperty &window_property);

    static void update();

    static void destroy();

    static bool getShouldClose();

    static void setShouldClose(bool isShouldClose);

    static void clear(float red, float green, float blue, float alpha);

    static void clear();

    static void setCursorMode(int cursorMode);
};

#endif  // WINDOW_H
