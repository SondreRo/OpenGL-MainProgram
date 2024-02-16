#include "Collisions.h"

#include <iostream>

#include "Model.h"
#include "Mesh.h"
#include "glm/ext/matrix_transform.hpp"


glm::vec3 SphereCollider::GetCenter()
{
	return LocalCenter; //Owner->GetLocation() + LocalCenter;
}

float SphereCollider::GetRadius()
{
	return LocalRadius;//Owner->GetScale().x * LocalRadius;
}

glm::mat4 SphereCollider::CaluclateMatrix()
{
	glm::mat4 MeshMatrix(1.0f);

	MeshMatrix *= glm::translate(glm::mat4(1.0f), LocalCenter);

	MeshMatrix *= glm::scale(glm::mat4(1.0f), glm::vec3(LocalRadius));
	glm::vec3 test = MeshMatrix[3];
	return MeshMatrix;
}

CollisionResult Collisions::CheckSphereCollisions(Model* MainModel, Model* OtherModel)
{
	// Create the collision result struct
	CollisionResult collision_result = CollisionResult();

	if (MainModel == nullptr || MainModel->Meshes.empty() || OtherModel == nullptr || OtherModel->Meshes.empty())
	{
		return collision_result;
	}

	collision_result.MainModel = MainModel;
	collision_result.OtherModel = OtherModel;

	for (auto MainMesh : MainModel->Meshes)
	{
		for (auto MainSphereCollider : MainMesh->SphereColliders)
		{
			for (auto OtherMesh : OtherModel->Meshes)
			{
				for (auto OtherSphereCollider : OtherMesh->SphereColliders)
				{
					if(SphereCollisionCalculation(MainSphereCollider, MainMesh, MainModel, OtherSphereCollider, OtherMesh, OtherModel))
					{
						collision_result.IsColliding = true;
					}
					else
					{
						collision_result.IsColliding = false;
					}
				}
			}
		}
	}
	
	return collision_result;
}

bool Collisions::SphereCollisionCalculation(SphereCollider* SphereCollider1, Mesh* Mesh1, Model* Model1, SphereCollider* SphereCollider2, Mesh* Mesh2, Model* Model2)
{
	//glm::vec3 Col2Loc = SphereCollider2->GetCenter() + Mesh2->GetLocation() + Model2->GetLocation();
	//glm::vec3 Col1Loc = SphereCollider1->GetCenter() + Mesh1->GetLocation() + Model1->GetLocation();

	glm::vec3 Col2Loc = (Model2->CalculateMeshMatrix() * Mesh2->CalculateMeshMatrix() * SphereCollider2->CaluclateMatrix())[3];
	glm::vec3 Col1Loc = (Model1->CalculateMeshMatrix() * Mesh1->CalculateMeshMatrix() * SphereCollider1->CaluclateMatrix())[3];

	float Col2Size = glm::length(Model2->CalculateMeshMatrix() * Mesh2->CalculateMeshMatrix() * SphereCollider2->CaluclateMatrix()[0]);
	float Col1Size = glm::length((Model1->CalculateMeshMatrix() * Mesh1->CalculateMeshMatrix() * SphereCollider1->CaluclateMatrix())[0]);
	
	std::cout <<
			Col2Loc.x << " " <<
			Col2Loc.y << " " <<
			Col2Loc.z << "    " <<
			Col1Loc.x << " " <<
			Col1Loc.y << " " <<
			Col1Loc.z << " " <<
				std::endl;
	float CenterDistance = glm::distance(Col2Loc, Col1Loc);

	//float DistanceAfterRadius = CenterDistance - SphereCollider1->GetRadius() - SphereCollider2->GetRadius();
	float DistanceAfterRadius = CenterDistance - Col2Size - Col1Size;

	if(DistanceAfterRadius <= 0)
	{
		//std::cout << SphereCollider1->GetOwner()->GetOwner()->GetName() << " collided with: " << SphereCollider1->GetOwner()->GetOwner()->GetName() << std::endl;
		return true;
	}

	return false;


}

