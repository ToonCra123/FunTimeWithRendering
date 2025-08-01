//
// Created by micha on 7/29/2025.
//

#include "App.h"

#include "Input.h"


App::App() : window(1920, 1080, "Cool Program") {
    Input::Initialize(window.GetWindow());
}

void App::Run() {
    while (!glfwWindowShouldClose(window.GetWindow())) {
        window.GetGraphics()->DoFrame();

        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }
}
