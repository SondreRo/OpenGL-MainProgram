#pragma once
#include "Model.h"

class Coin : public Model
{

	void Tick(float DeltaTime) override;
	void CollisionResponce(Mesh* OwnMesh, Mesh* OtherMesh, Model* OtherModel) override;

public:
	float RotationSpeed = 90;
	float Time = 0;
};

