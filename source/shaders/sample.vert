
attribute vec4 vertexPosition;
//attribute vec3 vertexColor;

//varying vec3 vColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{    
    //vColor = vertexColor;
    gl_Position = projection * view * model * vertexPosition;
}