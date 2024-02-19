#pragma once
#include "Collider.h"



class SphereCollider : public Collider
{
public:
	SphereCollider(glm::vec3 inLocation, float inScale);
	glm::vec3 GetCenter(); // Returns location
	float GetRadius(); // Returns x in Scale
};
