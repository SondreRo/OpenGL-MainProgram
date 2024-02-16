#pragma once

struct CollisionResult
{
	// Owners of collision
	// SphereCollider* MainSphereCollider{ nullptr }; // Should be changed for a collider class
	// Mesh* MainMesh{ nullptr };
	// Model* MainModel{ nullptr };
	//
	// // What we collided with:
	// SphereCollider* OtherSphereCollider{ nullptr };
	// Mesh* OtherMesh{ nullptr };
	// Model* OtherModel{ nullptr };

	bool IsColliding{ false };
};


class DefaultCollider
{
public:
	
};
