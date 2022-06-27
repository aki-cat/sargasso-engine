#version 330 core

// vertex attributes
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec4 vCol;
layout(location = 2) in vec3 vNorm;
layout(location = 3) in vec2 vUV;

uniform mat4 projMatrix;
uniform mat4 transform;

out vec4 color;

void main() {
    color = vCol;
    mat4 mvp = projMatrix * transform;
    gl_Position = mvp * vec4(vPos, 1.0);
}
