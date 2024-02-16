#pragma once
//#include "Mesh.h"
#include "glm/glm.hpp"

class Model;
class Mesh;

enum ColliderTypeEnum {Default, Sphere, Cube};

class MainCollider
{
public:
	ColliderTypeEnum colliderType = ColliderTypeEnum::Default;
	bool CollisionEnabled { true };
	Mesh* Owner{ nullptr };
};



class SphereCollider : public MainCollider
{
public:
	SphereCollider(glm::vec3 inCenter, float inRadius, bool inUseCollision, Mesh* SphereMesh)
	{
		LocalCenter = inCenter;
		LocalRadius = inRadius;
		UseCollision = inUseCollision;
		colliderType = ColliderTypeEnum::Sphere;
		this->SphereMesh = SphereMesh;
	}

	
	glm::vec3 LocalCenter;
	float LocalRadius;
	bool UseCollision;
	glm::vec3 GetCenter();
	float GetRadius();

	glm::mat4 CaluclateMatrix();

	Mesh* SphereMesh;
};

struct CollisionResult
{
	CollisionResult()
	{

	}
	// Owners of collision
	SphereCollider* MainSphereCollider{ nullptr }; // Should be changed for a collider class
	Mesh* MainMesh{ nullptr };
	Model* MainModel{ nullptr };

	// What we collided with:
	SphereCollider* OtherSphereCollider{ nullptr };
	Mesh* OtherMesh{ nullptr };
	Model* OtherModel{ nullptr };

	bool IsColliding{ false };
};

class Collisions
{
public:
	Collisions();
	static CollisionResult CheckSphereCollisions(Model* Model1, Model* Model2);
	static bool SphereCollisionCalculation(SphereCollider* SphereCollider1, Mesh* Mesh1, Model* Model1, SphereCollider* SphereCollider2, Mesh* Mesh2, Model* Model2);
};
