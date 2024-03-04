#pragma once
#include "Model.h"

class Character : public Model
{
public:
	void Tick(float DeltaTime) override;
	void CollisionResponce(Mesh* OwnMesh, Mesh* OtherMesh, Model* OtherModel) override;
	void HandleInput(GLFWwindow* window) override;
	float AddMovementInput(glm::vec3 Direction);

	float Speed = 5;
	bool onGround = false;
	float Gravity = 7;
};

