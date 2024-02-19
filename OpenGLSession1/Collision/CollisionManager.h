#pragma once
#include "SphereCollider.h"

class Model;

class CollisionManager
{
public:

	static void CheckModelsCollision(Model* Model1, Model* Model2);
	
	static bool CheckSphereCollision(glm::vec3 Loc1, float Rad1, glm::vec3 Loc2, float Rad2);

};
