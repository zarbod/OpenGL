#include "material.h"

Material Material::chrome = { glm::vec3(0.25, 0.25, 0.25), glm::vec3(0.4, 0.4, 0.4), glm::vec3(0.774597, 0.775597, 0.774597), 0.6 };
Material Material::obsidian = { glm::vec3(0.05375, 0.05, 0.06625), glm::vec3(0.18275, 0.17, 0.22525), glm::vec3(0.332741, 0.328634, 0.346435), 0.6 };
Material Material::white_plastic = { glm::vec3(0.0), glm::vec3(0.55), glm::vec3(0.70), 0.6 };

Material Material::mix(Material m1, Material m2, float mix) {
	return {
		m1.ambient * mix + m2.ambient * (1 - mix),
		m1.diffuse * mix + m2.diffuse * (1 - mix),
		m1.specular * mix + m2.specular * (1 - mix),
		m1.shininess * mix + m2.shininess * (1 - mix)
	};
}