#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	static Material chrome;
	static Material obsidian;
	static Material white_plastic;

	static Material mix(Material m1, Material m2, float mix);
};

#endif // !MATERIAL_H
