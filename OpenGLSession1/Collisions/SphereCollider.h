#pragma once
#include "Collisions.h"
#include "DefaultCollider.h"

class SphereCollider : public MainCollider
{
public:
	SphereCollider(glm::vec3 inCenter, float inRadius, bool inUseCollision, Mesh* inSphereMesh)
	{
		LocalCenter = inCenter;
		LocalRadius = inRadius;
		UseCollision = inUseCollision;
		colliderType = ColliderTypeEnum::Sphere;
		SphereMesh = inSphereMesh;
	}

	
	glm::vec3 LocalCenter;
	float LocalRadius;
	bool UseCollision;
	glm::vec3 GetCenter();
	float GetRadius();

	glm::mat4 CaluclateMatrix();

	Mesh* SphereMesh;
};
