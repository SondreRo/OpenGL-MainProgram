#include "Coin.h"

#include "Character.h"

void Coin::Tick(float DeltaTime)
{
	Model::Tick(DeltaTime);
	Time += DeltaTime;
	AddRotation(glm::vec3(0, RotationSpeed, 0) * DeltaTime);

	AddLocation(glm::vec3(0, (sin(Time) / 2) * DeltaTime, 0));
}

void Coin::CollisionResponce(Mesh* OwnMesh, Mesh* OtherMesh, Model* OtherModel)
{
	Model::CollisionResponce(OwnMesh, OtherMesh, OtherModel);

	if (dynamic_cast<Character*>(OtherModel))
	{
		IsVisible = false;
		IsCollisionDisabled = true;
	}
}
