//#include "Collisions.h"
//
//#include <iostream>
//#include <Eigen/src/Core/util/Meta.h>
//
//#include "../Model.h"
//#include "Mesh.h"
//#include "glm/ext/matrix_transform.hpp"
//
//
//glm::vec3 SphereCollider::GetCenter()
//{
//	return LocalCenter; //Owner->GetLocation() + LocalCenter;
//}
//
//float SphereCollider::GetRadius()
//{
//	return LocalRadius;//Owner->GetScale().x * LocalRadius;
//}
//
//glm::mat4 SphereCollider::CaluclateMatrix()
//{
//	glm::mat4 MeshMatrix(1.0f);
//
//	MeshMatrix *= glm::translate(glm::mat4(1.0f), LocalCenter);
//
//	MeshMatrix *= glm::scale(glm::mat4(1.0f), glm::vec3(LocalRadius));
//	glm::vec3 test = MeshMatrix[3];
//	return MeshMatrix;
//}
//
//glm::vec3 AxisAlignedBox::GetCenter()
//{
//	return Center;
//}
//
//glm::vec3 AxisAlignedBox::GetRadius()
//{
//	return Size;
//}
//
//glm::mat4 AxisAlignedBox::CaluclateMatrix()
//{
//	return glm::mat4(1);
//}
//
//CollisionResult Collisions::CheckSphereCollisions(Model* MainModel, Model* OtherModel)
//{
//	// Create the collision result struct
//	CollisionResult collision_result = CollisionResult();
//
//	if (MainModel == nullptr || MainModel->Meshes.empty() || OtherModel == nullptr || OtherModel->Meshes.empty())
//	{
//		return collision_result;
//	}
//
//	collision_result.MainModel = MainModel;
//	collision_result.OtherModel = OtherModel;
//
//	for (auto MainMesh : MainModel->Meshes)
//	{
//		for (auto MainSphereCollider : MainMesh->SphereColliders)
//		{
//			for (auto OtherMesh : OtherModel->Meshes)
//			{
//				for (auto OtherSphereCollider : OtherMesh->SphereColliders)
//				{
//					if(SphereCollisionCalculation(MainSphereCollider, MainMesh, MainModel, OtherSphereCollider, OtherMesh, OtherModel))
//					{
//						collision_result.IsColliding = true;
//					}
//					else
//					{
//						collision_result.IsColliding = false;
//					}
//				}
//			}
//		}
//	}
//	
//	return collision_result;
//}
//
//CollisionResult Collisions::CheckAxisAlignedBoxCollisions(Model* MainModel, Model* OtherModel)
//{
//	// Create the collision result struct
//	CollisionResult collision_result = CollisionResult();
//
//	if (MainModel == nullptr || MainModel->Meshes.empty() || OtherModel == nullptr || OtherModel->Meshes.empty())
//	{
//		return collision_result;
//	}
//
//	collision_result.MainModel = MainModel;
//	collision_result.OtherModel = OtherModel;
//
//	for (auto MainMesh : MainModel->Meshes)
//	{
//		for (auto MainAxisAlignedBoxCollider : MainMesh->AxisAlignedBoxColliders)
//		{
//			for (auto OtherMesh : OtherModel->Meshes)
//			{
//				for (auto OtherAxisAlignedBoxCollider : OtherMesh->AxisAlignedBoxColliders)
//				{
//					if(AxisAlignedBoxCollisionCalculation(MainAxisAlignedBoxCollider, MainMesh, MainModel, OtherAxisAlignedBoxCollider, OtherMesh, OtherModel))
//					{
//						collision_result.IsColliding = true;
//					}
//					else
//					{
//						collision_result.IsColliding = false;
//					}
//				}
//			}
//		}
//	}
//	
//	return collision_result;
//}
//
//bool Collisions::SphereCollisionCalculation(SphereCollider* SphereCollider1, Mesh* Mesh1, Model* Model1, SphereCollider* SphereCollider2, Mesh* Mesh2, Model* Model2)
//{
//	glm::vec3 Col2Loc = (Model2->CalculateMeshMatrix() * Mesh2->CalculateMeshMatrix() * SphereCollider2->CaluclateMatrix())[3];
//	glm::vec3 Col1Loc = (Model1->CalculateMeshMatrix() * Mesh1->CalculateMeshMatrix() * SphereCollider1->CaluclateMatrix())[3];
//
//	float Col2Size = glm::length(Model2->CalculateMeshMatrix() * Mesh2->CalculateMeshMatrix() * SphereCollider2->CaluclateMatrix()[0]);
//	float Col1Size = glm::length((Model1->CalculateMeshMatrix() * Mesh1->CalculateMeshMatrix() * SphereCollider1->CaluclateMatrix())[0]);
//	
//	float CenterDistance = glm::distance(Col2Loc, Col1Loc);
//	float DistanceAfterRadius = CenterDistance - Col2Size - Col1Size;
//
//	if(DistanceAfterRadius <= 0)
//	{
//		return true;
//	}
//
//	return false;
//
//
//}
//
//bool Collisions::AxisAlignedBoxCollisionCalculation(AxisAlignedBox* AxisAlignedBox1, Mesh* Mesh1, Model* Model1,
//	AxisAlignedBox* AxisAlignedBox2, Mesh* Mesh2, Model* Model2)
//{
//	glm::vec3 bl = (Model2->CalculateMeshMatrix() * Mesh2->CalculateMeshMatrix() * AxisAlignedBox2->CaluclateMatrix())[3];
//	glm::vec3 al = (Model1->CalculateMeshMatrix() * Mesh1->CalculateMeshMatrix() * AxisAlignedBox1->CaluclateMatrix())[3];
//
//
//
//	AxisAlignedBox* a = AxisAlignedBox1;
//	AxisAlignedBox* b = AxisAlignedBox2;
//	
//	//glm::vec3 Col2Size = Model2->CalculateMeshMatrix() * Mesh2->CalculateMeshMatrix() * AxisAlignedBox2->CaluclateMatrix();
//	//glm::vec3 Col1Size = Model1->CalculateMeshMatrix() * Mesh1->CalculateMeshMatrix() * AxisAlignedBox1->CaluclateMatrix();
//	
//	if (
//		a->Center.x + al.x <= b->Center.x + bl.x &&
//		a->Center.x + al.x >= b->Center.x + bl.x &&
//		a->Center.y + al.y <= b->Center.y + bl.y &&
//		a->Center.y + al.y >= b->Center.y + bl.y &&
//		a->Center.z + al.z <= b->Center.z + bl.z &&
//		a->Center.z + al.z >= b->Center.z + bl.z)
//	{
//		return true;
//	}
//	return false;
//}
//
