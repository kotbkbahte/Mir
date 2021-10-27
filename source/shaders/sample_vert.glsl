#version 460 
layout (location = 0) in vec4 vertexPosition;

uniform vec3 color;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
out vec3 Color;

void main()
{
    gl_Position = projection * model * view * vertexPosition;
    Color = color;
} 