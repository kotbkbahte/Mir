#version 460 
uniform sampler2D texture;
uniform vec3 textColor;

in vec2 vTexCoord;
out vec4 FragColor;
    
    
    
void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(texture, vTexCoord).r);
    FragColor = vec4(textColor, 1.0) * sampled;
    
    
}  
