#version 330 core

out vec4 FragColor;

void main() {
    float x = gl_FragCoord.x;
    float y = gl_FragCoord.y;

    FragColor = vec4(x/1920, y/1080, 1.0, 1.0);
}