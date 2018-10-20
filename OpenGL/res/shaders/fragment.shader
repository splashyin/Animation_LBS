#version 430 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture_diffuse1;


void main()
{
	//FragColor = texture(texture_diffuse1, TexCoord);
	FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
}