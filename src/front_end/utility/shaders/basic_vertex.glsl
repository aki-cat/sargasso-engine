#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 projection_view;

void main(){
    gl_Position = projection_view * vec4(vertexPosition_modelspace, 1.0);
}
