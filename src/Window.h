//
// Created by micha on 7/29/2025.
//

#pragma once
#include <memory>

#include "Graphics.h"
#include "GLFW/glfw3.h"

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();
    GLFWwindow* GetWindow() const { return window; };
    Graphics* GetGraphics() { return gfx.get(); }
    void Start();
private:
    GLFWwindow* window;
    std::unique_ptr<Graphics> gfx;
};
