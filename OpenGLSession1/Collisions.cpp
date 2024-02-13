#include "Collisions.h"

#include <iostream>

#include "Model.h"
#include "Mesh.h"


glm::vec3 SphereCollider::GetCenter()
{
	return Owner->GetLocation() + LocalCenter;
}

float SphereCollider::GetRadius()
{
	return Owner->GetScale().x * LocalRadius;
}

CollisionResult Collisions::CheckSphereCollisions(Model* MainModel, Model* OtherModel)
{
	// Create the collision result struct
	CollisionResult collision_result = CollisionResult();

	if (MainModel == nullptr || MainModel->Meshes.empty())
	{
		return collision_result;
	}
	if (OtherModel == nullptr || OtherModel->Meshes.empty())
	{
		return collision_result;
	}

	collision_result.MainModel = MainModel;
	collision_result.OtherModel = OtherModel;


	std::vector<SphereCollider*> MainSphereColliders = MainModel->GetSphereColliders();
	std::vector<SphereCollider*> OtherSphereColliders = OtherModel->GetSphereColliders();

	if (MainSphereColliders.empty() || OtherSphereColliders.empty())
	{
		return collision_result;
	}

	for (auto main_sphere_collider : MainSphereColliders)
	{
		collision_result.MainSphereCollider = main_sphere_collider;
		for (auto other_sphere_collider : OtherSphereColliders)
		{
			collision_result.OtherSphereCollider = other_sphere_collider;
			if (SphereCollisionCalculation(main_sphere_collider, other_sphere_collider))
			{
				collision_result.IsColliding = true;
			}
			else
			{
				collision_result.IsColliding = false;
			}
		}
	}
	
	return collision_result;
}

bool Collisions::SphereCollisionCalculation(SphereCollider* SphereCollider1, SphereCollider* SphereCollider2)
{
	float CenterDistance = glm::distance(SphereCollider2->GetCenter(), SphereCollider1->GetCenter());
	float DistanceAfterRadius = CenterDistance - SphereCollider1->GetRadius() - SphereCollider2->GetRadius();

	if(DistanceAfterRadius <= 0)
	{
		//std::cout << SphereCollider1->GetOwner()->GetOwner()->GetName() << " collided with: " << SphereCollider1->GetOwner()->GetOwner()->GetName() << std::endl;
		return true;
	}

	return false;


}

