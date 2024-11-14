//
// Created by rmamin1337 on 12.11.2024.
//

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <GLFW/glfw3.h>

#include <unordered_map>

#include "InputState.h"

class EventManager {
    static std::unordered_map<int, InputState>
        _keyStates;  // Map for key and mouse states.
public:
    static int _currentFrameNumber;  // Current frame number.
    static float _deltaX;            // Mouse offsets.
    static float _deltaY;            // Mouse offsets.
    static float _mouseX;            // Mouse position.
    static float _mouseY;            // Mouse position.
    static bool _isCursorLocked;     // Cursor lock flag.
    static bool _isCursorStarted;    // Cursor tracking start flag.

    static int initialize();

    // Event Handlers.
    static void keyCallback(
        GLFWwindow *window, int key, int scancode, int action, int mods
    );

    static void mouseButtonCallback(
        GLFWwindow *window, int button, int action, int mods
    );

    static void cursorPositionCallback(
        GLFWwindow *window, double xPosition, double yPosition
    );

    static void windowSizeCallback(GLFWwindow *window, int width, int height);

    // Functions for checking the status of keys/buttons.
    static bool isKeyPressed(int keycode);

    static bool isKeyJustPressed(int keycode);

    static bool isMouseButtonPressed(int button);

    static bool isMouseButtonJustPressed(int button);

    // Function for setting cursor mode.
    static void toggleCursor();

    // Event Handling Function.
    static void pullEvents();
};

#endif  // EVENTMANAGER_H
