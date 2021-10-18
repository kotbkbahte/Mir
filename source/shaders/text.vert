#version 460 
layout (location = 0) in vec4  vertexPosition;
layout (location = 1) in vec2  textureCoordinates;


out vec2 vTexCoord;
out vec4 gl_Position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main()
{   
    vTexCoord = textureCoordinates;
    gl_Position =  projection * view * model * vertexPosition;
}