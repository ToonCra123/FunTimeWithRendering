//
// Created by micha on 7/30/2025.
//

#pragma once
#include "GLFW/glfw3.h"

class Input {
public:
    static void Initialize(GLFWwindow* window);  // call once at startup
    static Input* GetInstance();

    bool GetKeyDown(int keycode) const;

    static void SetLockCursor(bool lockCursor);

    /// @returns cursor pos in input variables
    static void GetCursorPos(double &x, double &y);

private:
    explicit Input(GLFWwindow* window);  // private constructor
    GLFWwindow* mWindow;

    static Input* instance;
};
