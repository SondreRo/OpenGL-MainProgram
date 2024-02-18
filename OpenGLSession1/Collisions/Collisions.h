//#pragma once
////#include "Mesh.h"
//#include "glm/glm.hpp"
//
//class Model;
//class Mesh;
//
//enum ColliderTypeEnum {Default, Sphere, Cube};
//
//class MainCollider
//{
//public:
//	ColliderTypeEnum colliderType = ColliderTypeEnum::Default;
//	bool CollisionEnabled { true };
//	Mesh* Owner{ nullptr };
//};
//
//
//
//
//
//	class AxisAlignedBox : public MainCollider
//	{
//	public:
//		AxisAlignedBox(glm::vec3 inCenter, glm::vec3 inSize, bool inUseCollision, Mesh* inBoxMesh)
//		{
//			Center = inCenter;
//			Size = inSize;
//			UseCollision = inUseCollision;
//			BoxMesh = inBoxMesh;
//		}
//
//		glm::vec3 Center;
//		glm::vec3 Size;
//		bool UseCollision;
//		Mesh* BoxMesh;
//
//		glm::vec3 GetCenter();
//		glm::vec3 GetRadius();
//
//		glm::mat4 CaluclateMatrix();
//	};
//
//
//class Collisions
//{
//public:
//	Collisions();
//	static CollisionResult CheckSphereCollisions(Model* MainModel, Model* OtherModel);
//	static CollisionResult CheckAxisAlignedBoxCollisions(Model* MainModel, Model* OtherModel);
//	
//	static bool SphereCollisionCalculation(SphereCollider* SphereCollider1, Mesh* Mesh1, Model* Model1, SphereCollider* SphereCollider2, Mesh* Mesh2, Model* Model2);
//	static bool AxisAlignedBoxCollisionCalculation(AxisAlignedBox* AxisAlignedBox1, Mesh* Mesh1, Model* Model1, AxisAlignedBox* AxisAlignedBox2, Mesh* Mesh2, Model* Model2);
//};
