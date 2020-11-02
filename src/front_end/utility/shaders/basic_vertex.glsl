#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 projection;
uniform mat4 view;

void main(){
    gl_Position = projection * view * vec4(vertexPosition_modelspace, 1.0);
}
