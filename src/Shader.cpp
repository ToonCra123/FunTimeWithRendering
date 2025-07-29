//
// Created by micha on 7/29/2025.
//

#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/glad.h"

Shaders::Shaders(const char* vertexShaderFname, const char* fragmentShaderFname) {
    std::ifstream file(vertexShaderFname);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << vertexShaderFname << std::endl;
        exit(1);
    }

    std::stringstream vbuffer;
    vbuffer << file.rdbuf();
    file.close();

    vertexShaderSource = vbuffer.str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vsrc = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vsrc, nullptr);
    glCompileShader(vertexShader);

    // idk
    std::ifstream ffile(fragmentShaderFname);

    if (!ffile.is_open()) {
        std::cerr << "Error opening file " << fragmentShaderFname << std::endl;
        exit(1);
    }

    std::stringstream fbuffer;
    fbuffer << ffile.rdbuf();
    ffile.close();

    fragmentShaderSource = fbuffer.str();

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fsrc = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fsrc, nullptr);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

Shaders::~Shaders() {
    glDeleteProgram(program);
}
