uniform sampler2D texture;

varying vec2 vTexCoord;

void main()
{
    vec4 color = texture2D(texture, vTexCoord);
    gl_FragColor = color;
}