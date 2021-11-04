#version 460 
uniform sampler2D texture;
uniform float colorLightness;
uniform bool isHovered;
uniform vec3 strokeColor;

in vec2 vTexCoord;
out vec4 FragColor;

vec3 czm_saturation(vec3 rgb, float adjustment);
vec3 czm_hue(vec3 rgb, float adjustment);
vec3 czm_gammaCorrect(vec3 color);

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    if(isHovered)
    {
        FragColor = vec4(strokeColor, 1.0f);
        return;
    }
    vec4 color = texture2D(texture, vTexCoord);
    
    float avr = (color.r + color.g + color.b) / 3.0;
   
    if(avr < 0.7 && colorLightness != -1.0)
    {
        FragColor = vec4(color.rgb * colorLightness, color.a);
        return;
    }
    
    FragColor = color;
    return;
}


vec3 czm_saturation(vec3 rgb, float adjustment)
{
    // Algorithm from Chapter 16 of OpenGL Shading Language
    const vec3 W = vec3(0.2125, 0.7154, 0.0721);
    vec3 intensity = vec3(dot(rgb, W));
    return mix(intensity, rgb, adjustment);
}

vec3 czm_hue(vec3 rgb, float adjustment)
{
    const mat3 toYIQ = mat3(0.299,     0.587,     0.114,
                            0.595716, -0.274453, -0.321263,
                            0.211456, -0.522591,  0.311135);
    const mat3 toRGB = mat3(1.0,  0.9563,  0.6210,
                            1.0, -0.2721, -0.6474,
                            1.0, -1.107,   1.7046);
    
    vec3 yiq = toYIQ * rgb;
    float hue = atan(yiq.z, yiq.y) + adjustment;
    float chroma = sqrt(yiq.z * yiq.z + yiq.y * yiq.y);
    
    vec3 color = vec3(yiq.x, chroma * cos(hue), chroma * sin(hue));
    return toRGB * color;
}

vec3 czm_gammaCorrect(vec3 color) 
{
#ifdef HDR
    color = pow(color, vec3(czm_gamma));
#endif
    return color;
}

vec4 czm_gammaCorrect(vec4 color) {
#ifdef HDR
    color.rgb = pow(color.rgb, vec3(czm_gamma));
#endif
    return color;
}