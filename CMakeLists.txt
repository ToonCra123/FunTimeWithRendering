cmake_minimum_required(VERSION 3.20)
project(opengl_renderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add glad source file
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(opengl_renderer
        main.cpp
        src/Graphics.cpp
        src/Shader.cpp
        src/Window.cpp
        src/App.cpp
        src/App.h
)

# Include GLFW and glad headers
target_include_directories(opengl_renderer PRIVATE
        external/glfw/include
        external/glad/include
)

# Link to glfw3.lib, glad, and system OpenGL
target_link_libraries(opengl_renderer
        PRIVATE
        glad
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib-vc2022/glfw3.lib
        opengl32
)

if (MSVC)
    set_target_properties(opengl_renderer PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()