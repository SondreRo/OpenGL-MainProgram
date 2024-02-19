#pragma once

#include <../glm/glm.hpp>

class Mesh;

class Collider
{


protected:
	glm::vec3 Location {glm::vec3(0)};
	glm::vec3 Rotation {glm::vec3(0)};
	glm::vec3 Scale {glm::vec3(1)};
public:
	Mesh* DisplayMesh;

	void SetDisplayMesh(Mesh* inMesh);
	
	void SetLocation(glm::vec3 NewLocation);
	glm::vec3 GetLocation();

	void SetRotation(glm::vec3 NewRotation);
	glm::vec3 GetRotation();

	void SetScale(glm::vec3 NewScale);
	glm::vec3 GetScale();

	glm::mat4 CalculateMatrix();
};
