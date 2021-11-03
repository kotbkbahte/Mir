#version 460 
layout (location = 0) in vec4  vertexPosition;
layout (location = 1) in vec2  textureCoordinates;

uniform mat4 projection;
uniform mat4 model;

out vec2 vTexCoord;

void main()
{    
    vTexCoord = textureCoordinates;
    gl_Position = projection * model * vertexPosition;
}