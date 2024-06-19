#pragma once

#include <glm.hpp>

class Lighting {
private:
	glm::vec3 lightDir;
	glm::vec3 lightColor;
	float ambientStrength;
public:
	Lighting();

	inline glm::vec3& getLightDir() { return lightDir; }
	inline glm::vec3& getLightColor() { return lightColor; }
	inline float& getAmbientStrength() { return ambientStrength; }
};