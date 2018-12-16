#version 450 core

in vec3 VertexPosition;
in vec3 VertexColor;

out vec3 pos;
out vec3 col;

void main() {
    pos = VertexPosition;
    col = VertexColor;
    gl_Position = vec4(pos, 1.0);
}
