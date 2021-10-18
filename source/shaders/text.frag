#version 460 
uniform sampler2D texture;

in vec2 vTexCoord;
out vec4 gl_FragColor;

void main()
{
    vec4 color = texture2D(texture, vTexCoord);
    gl_FragColor = color;
}