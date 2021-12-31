#version 460 
layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in vec2 textureCoordinates;
 
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform mat4 textureCoordScalePos;
uniform float frame;

out vec2 vTexCoord;

void main()
{    
    //vec4 tc = vec4(textureCoordinates.x + frame, textureCoordinates.y, 0, 1.0);
    vTexCoord = textureCoordinates;
    gl_Position = projection * view * model * vertexPosition;
}