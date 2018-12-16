#version 450 core

in vec3 pos;
in vec3 col;

layout(location = 0) out vec4 fColor;

void main() {
    fColor = vec4(col, 1.);
}
