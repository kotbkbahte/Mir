#version 460 
uniform sampler2D diffuseTex;
uniform vec4 textColor;

in vec2 vTexCoord;
out vec4 FragColor;
    
uniform vec4 diffuseColor;	// actual color for this text
uniform vec4 outlineColor;
    
void main()
{
    //vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(texture, vTexCoord).r);
    //FragColor = vec4(textColor, 1.0) * sampled;
    
    vec2 tex = texture2D(diffuseTex, vTexCoord).rg;

	// color consists of the (diffuse color * main alpha) + (background color * outline alpha)
	vec3 color = (textColor.rgb * tex.r) + (outlineColor.rgb * tex.g);

	// make the main alpha more pronounced, makes small text sharper
	tex.r = clamp(tex.r * 2.0, 0.0, 1.0);

	// alpha is the sum of main alpha and outline alpha
	// main alpha is main font color alpha
	// outline alpha is the stroke or shadow alpha
	float mainAlpha = tex.r * textColor.a;
	float outlineAlpha = tex.g * outlineColor.a * textColor.a;
	FragColor = vec4(color, mainAlpha + outlineAlpha);
}  
