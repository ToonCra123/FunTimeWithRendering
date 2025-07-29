//
// Created by micha on 7/29/2025.
//

#pragma once
#include <string>

class Shaders {
public:
    Shaders(const char *vertexShaderFname, const char *fragmentShaderFname);
    ~Shaders();
    int GetProgram() const { return program; };
private:
    int vertexShader;
    int fragmentShader;
    int program;
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
};
