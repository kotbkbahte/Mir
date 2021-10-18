//varying vec3 vColor; 
uniform vec3 uColor;

void main()
{
    gl_FragColor = vec4(uColor, 0.7);
}