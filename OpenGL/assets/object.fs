#version 330 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
//in vec3 color;
//in vec2 TexCoord;
//in float mixture;

//uniform vec4 mainColor;

//uniform sampler2D texture1;
//uniform sampler2D texture2;
//uniform float mixVal;
uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main() {
	//FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	//FragColor = vec4(color, 1.0);
	//FragColor = texture(texture2, TexCoord);
	//FragColor = vec4(0.5f, 0.1f, 0.7f, 1.0f);

	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixVal);
	vec3 ambient = light.ambient * material.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * material.diffuse;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * 128);
	vec3 specular = light.specular * spec * material.specular;

	FragColor = vec4(vec3(ambient + diffuse + specular), 1.0);
}