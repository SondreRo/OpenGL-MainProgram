
#include "SphereCollider.h"

SphereCollider::SphereCollider(glm::vec3 inLocation, float inScale)
{
	Location = inLocation;
	Scale = glm::vec3(inScale);
}

glm::vec3 SphereCollider::GetCenter()
{
	return Location;
}

float SphereCollider::GetRadius()
{
	return Scale.x;
}
