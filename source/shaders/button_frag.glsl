#version 460 
uniform sampler2D texture;
uniform float colorLightness;
uniform bool isHovered;
uniform vec3 strokeColor;

in vec2 vTexCoord;
out vec4 FragColor;


void main()
{
    if(isHovered)
    {
        FragColor = vec4(strokeColor, 1.0f);
        return;
    }
    vec4 color = texture2D(texture, vTexCoord);
    
    if( (color.r >= colorLightness) && (color.r <= 0.6) )
    {
        color.r = color.r * colorLightness;
        color.b = color.b * colorLightness;
        color.g = color.g * colorLightness;
    }
    
    
    
    FragColor = color;
    return;
}