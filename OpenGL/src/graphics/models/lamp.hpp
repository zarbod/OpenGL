#ifndef LAMP_HPP
#define LAMP_HPP

#include "../models/cube.hpp"

class Lamp : public Cube {
public:
	glm::vec3 lightColor;
	
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Lamp(glm::vec3 lightColor,
		glm::vec3 ambient,
		glm::vec3 diffuse,
		glm::vec3 specular,
		glm::vec3 pos,
		glm::vec3 size)
		: lightColor(lightColor),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular),
		Cube(pos, size, Material::obsidian, false) {}

	void render(Shader shader) {
		shader.setFloat3("lightColor", lightColor);

		Cube::render(shader);
	}
};
 
#endif // !LAMP_HPP