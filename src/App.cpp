//
// Created by micha on 7/29/2025.
//

#include "App.h"


App::App() : window(800, 600, "Kys") {
}

void App::Run() {
    while (!glfwWindowShouldClose(window.GetWindow())) {
        window.GetGraphics()->DoFrame();

        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }
}
