#version 460 
uniform sampler2D texture;

out vec4 FragColor;
in vec2 vTexCoord;


void main()
{
    vec4 color = texture2D(texture, vTexCoord);
    FragColor = color;   
}