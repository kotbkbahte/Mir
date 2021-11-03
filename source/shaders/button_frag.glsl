#version 460 
uniform sampler2D texture;
uniform float colorLightness;

in vec2 vTexCoord;
out vec4 FragColor;


void main()
{
    vec4 color = texture2D(texture, vTexCoord);
       
    
    if( (color.r >= colorLightness) && (color.r <= 0.6) )
    {
        color.r = color.r * colorLightness;
        color.b = color.b * colorLightness;
        color.g = color.g * colorLightness;
    }
    
    
    
    FragColor = color;
}