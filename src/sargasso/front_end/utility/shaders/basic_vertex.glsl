#version 310

uniform mat4 camera_transform;

attribute vec3 vertex;

varying vec4 color;

void main() {
    gl_Position = camera_transform * vec4(vertex, 1.0);
    color = vec4(1.0, 1.0, 1.0, 1.0);
}
