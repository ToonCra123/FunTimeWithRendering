cmake_minimum_required(VERSION 3.20)
project(opengl_renderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- GLAD ----
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# ---- GLM -----
include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

# ---- Source files ----
set(SOURCES
        main.cpp
        src/Graphics.cpp
        src/Shader.cpp
        src/Window.cpp
        src/App.cpp
        src/App.h
        src/Camera.cpp
        src/Camera.h
        src/Input.cpp
        src/Input.h
        src/Objects/Object.cpp
        src/Objects/Object.h
)

add_executable(opengl_renderer ${SOURCES})

target_include_directories(opengl_renderer PRIVATE
        external/glfw/include
        external/glad/include
)

# ---- Platform-specific linking ----
if (MSVC)
    # Windows / MSVC settings
    target_link_libraries(opengl_renderer
            PRIVATE
            glad
            glm::glm
            ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib-vc2022/glfw3.lib
            opengl32
    )

    # Build as Windows GUI app (no console window)
    set_target_properties(opengl_renderer PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

    # Define GLFW_STATIC if you are linking the static glfw library
    target_compile_definitions(opengl_renderer PRIVATE GLFW_STATIC)

    # Optionally: Use static MSVC runtime (optional, see explanation)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

elseif(APPLE)
    # macOS settings

    # Find system GLFW (assuming installed via brew or otherwise)
    find_package(glfw3 3.3 REQUIRED)

    target_link_libraries(opengl_renderer
            PRIVATE
            glad
            glm::glm
            glfw
            "-framework OpenGL"
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
    )

else()
    message(WARNING "Unsupported platform. You may need to configure libraries yourself.")
endif()