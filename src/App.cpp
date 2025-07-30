//
// Created by micha on 7/29/2025.
//

#include "App.h"


App::App() : window(1920, 1080, "Kys") {
}

void App::Run() {
    while (!glfwWindowShouldClose(window.GetWindow())) {
        window.GetGraphics()->DoFrame();

        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }
}
