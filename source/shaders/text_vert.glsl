#version 460 
layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in vec2 textureCoordinates;

uniform mat4 projection;
out vec2 vTexCoord;

void main()
{
    gl_Position = projection * vec4(vertexPosition.xy, 0.0, 1.0);
    vTexCoord = textureCoordinates;
} 