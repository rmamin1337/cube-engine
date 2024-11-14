//
// Created by rmamin1337 on 12.11.2024.
//

#include "EventManager.h"

#include "../window/Window.h"

std::unordered_map<int, InputState> EventManager::_keyStates;
int EventManager::_currentFrameNumber = 0;
float EventManager::_deltaX = 0.0f;
float EventManager::_deltaY = 0.0f;
float EventManager::_mouseX = 0.0f;
float EventManager::_mouseY = 0.0f;
bool EventManager::_isCursorLocked = false;
bool EventManager::_isCursorStarted = false;

int EventManager::initialize() {
    GLFWwindow *window = Window::instance;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    return 0;
}

void EventManager::keyCallback(
    GLFWwindow *window, const int key, int scancode, const int action, int mods
) {
    if (action == GLFW_PRESS || action == GLFW_RELEASE) {
        _keyStates[key].isPressed = (action == GLFW_PRESS);
        _keyStates[key].clickedFrameNumber = _currentFrameNumber;
    }
}

void EventManager::mouseButtonCallback(
    GLFWwindow *window, const int button, const int action, int mods
) {
    const int buttonIndex = 1024 + button;
    if (action == GLFW_PRESS || action == GLFW_RELEASE) {
        _keyStates[buttonIndex].isPressed = (action == GLFW_PRESS);
        _keyStates[buttonIndex].clickedFrameNumber = _currentFrameNumber;
    }
}

void EventManager::cursorPositionCallback(
    GLFWwindow *window, const double xPosition, const double yPosition
) {
    if (_isCursorStarted) {
        _deltaX += xPosition - _mouseX;
        _deltaY += yPosition - _mouseY;
    } else {
        _isCursorStarted = true;
    }
    _mouseX = xPosition;
    _mouseY = yPosition;
}

void EventManager::windowSizeCallback(
    GLFWwindow *window, const int width, const int height
) {
    glViewport(0, 0, width, height);
    Window::width = width;
    Window::height = height;
}

bool EventManager::isKeyPressed(const int keycode) {
    const auto it = _keyStates.find(keycode);
    return (it != _keyStates.end() && it->second.isPressed);
}

bool EventManager::isKeyJustPressed(const int keycode) {
    const auto it = _keyStates.find(keycode);
    return (
        it != _keyStates.end() && it->second.isPressed &&
        it->second.clickedFrameNumber == _currentFrameNumber
    );
}

bool EventManager::isMouseButtonPressed(const int button) {
    return isKeyPressed(1024 + button);  // Index shift for mouse buttons.
}

bool EventManager::isMouseButtonJustPressed(const int button) {
    return isKeyJustPressed(1024 + button);  // Index shift for mouse buttons.
}

void EventManager::toggleCursor() {
    _isCursorLocked = !_isCursorLocked;
    Window::setCursorMode(
        _isCursorLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL
    );
}

void EventManager::pullEvents() {
    _currentFrameNumber++;
    _deltaX = 0.0f;
    _deltaY = 0.0f;
    glfwPollEvents();
}
