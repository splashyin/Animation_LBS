#version 430 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	//FragColor = texture(ourTexture, TexCoord);
	
	//object color : corral color
	vec3 objectColor = vec3(1.0f, 0.5f, 0.31f);

	//Ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	//Diffuse 
	//normalize both the normal and the resulting direction vector;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	//calculate the diffuse impact
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;

	FragColor = vec4(result, 1.0);


}