//
// Created by micha on 7/30/2025.
//

#include "Input.h"

Input* Input::instance = nullptr;

void Input::Initialize(GLFWwindow* window) {
    if (instance == nullptr) {
        instance = new Input(window);
    }
}

Input* Input::GetInstance() {
    return instance;
}

Input::Input(GLFWwindow* window)
    : mWindow(window) {}

bool Input::GetKeyDown(int keycode) const {
    return glfwGetKey(mWindow, keycode) == GLFW_PRESS;
}