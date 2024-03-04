#pragma once
#include "SphereCollider.h"

class Model;

class CollisionManager
{
public:

	static void CheckModelsCollision(Model* Model1, Model* Model2);

	static void SphereCollisionGetters(Model* Model1, Mesh* Mesh1, Model* Model2, Mesh* Mesh2);
	static void AxisAlignedBoxCollisionGetters(Model* Model1, Mesh* Mesh1, Model* Model2, Mesh* Mesh2);


	static bool CheckSphereCollision(glm::vec3 Loc1, float Rad1, glm::vec3 Loc2, float Rad2);
	static bool CheckAxisAlignedBoxCollision(glm::vec3 Loc1, glm::vec3 Scale1, glm::vec3 Loc2, glm::vec3 Scale2);
};
