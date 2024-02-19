#include "CollisionManager.h"

#include <iostream>
#include <../glm/glm.hpp>
#include "../Model.h"

void CollisionManager::CheckModelsCollision(Model* Model1, Model* Model2)
{
	if (Model1->Meshes.empty() || Model2->Meshes.empty()) return;

	
	for (auto Mesh1 : Model1->Meshes)
	{
		if (Mesh1->SphereColliders.empty()) continue;
		for (auto SphCol1 : Mesh1->SphereColliders)
		{
			for (auto Mesh2 : Model2->Meshes)
			{
				if (Mesh2->SphereColliders.empty()) continue;
				for (auto SphCol2 : Mesh2->SphereColliders)
				{
					
					glm::mat4 Mat1 = Model1->CalculateMeshMatrix() * Mesh1->CalculateMeshMatrix() * SphCol1->CalculateMatrix();
					glm::mat4 Mat2 = Model2->CalculateMeshMatrix() * Mesh2->CalculateMeshMatrix() * SphCol2->CalculateMatrix();

					glm::vec3 Scale1 = glm::vec3(glm::length(glm::vec3(Mat1[0])), glm::length(glm::vec3(Mat1[1])), glm::length(glm::vec3(Mat1[2])));
					float Radius1 = SphCol1->GetRadius() * Scale1.x;

					glm::vec3 Scale2 = glm::vec3(glm::length(glm::vec3(Mat2[0])), glm::length(glm::vec3(Mat2[1])), glm::length(glm::vec3(Mat2[2])));
					float Radius2 = SphCol2->GetRadius() * Scale2.x;
					CheckSphereCollision(Mat1[3], Radius1, Mat2[3], Radius2);
				}
			}
		}
	}
}

bool CollisionManager::CheckSphereCollision(glm::vec3 Loc1, float Rad1, glm::vec3 Loc2, float Rad2)
{
	float Distance = glm::distance(Loc1, Loc2);
	float DistanceAfterRadius = Distance - abs(Rad1) - abs(Rad2);
	if (DistanceAfterRadius <= 0)
	{
		//std::cout << "Collision" << std::endl;
		// TODO Add collision physics response.
		return true;
	}
	std::cout << std::endl;

	return false;
}
