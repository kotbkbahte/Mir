attribute vec4 vertexPosition;
attribute vec2 textureCoordinates;

uniform float time;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec2 vTexCoord;
float M_PI = 3.14159265358979323846264338327950288;

void main()
{    
    vTexCoord = textureCoordinates;
    
    float t1 = cos( vertexPosition.x * (2 * M_PI) + time / 200.0 );
    float t2 = sin( vertexPosition.z * (2 * M_PI) + time / 200.0 );
    
    vertexPosition.y += (t1 + t2) / 20.0f ;
    
    gl_Position = projection * view * model * vertexPosition;
}