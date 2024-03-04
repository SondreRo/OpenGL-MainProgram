#include "Character.h"

#include <iostream>

#include "GLFW/glfw3.h"

void Character::Tick(float DeltaTime)
{
	Model::Tick(DeltaTime);
	std::cout << onGround << std::endl;
	if(onGround == false)
	{
		Velocity -= glm::vec3(0, Gravity, 0) * DeltaTime;
	}

	onGround = false;
	AddLocation(Velocity * DeltaTime);


	Velocity.x *= 1 - (5 * DeltaTime);
	Velocity.z *= 1 - (5 * DeltaTime);


}

void Character::CollisionResponce(Mesh* OwnMesh, Mesh* OtherMesh, Model* OtherModel)
{
	Model::CollisionResponce(OwnMesh, OtherMesh, OtherModel);
	if (GetLocation().y > OtherModel->GetLocation().y)
	{
		onGround = true;
		Velocity.y = 0;
		return;
	}
	else
	{
		onGround = false;
	}

	if (GetLocation().x > OtherModel->GetLocation().x)
	{
		onGround = true;
		Velocity.x *= -1;
	}
	if (GetLocation().x < OtherModel->GetLocation().x)
	{
		onGround = true;
		Velocity.x *= -1;
	}
}

void Character::HandleInput(GLFWwindow* window)
{
	Model::HandleInput(window);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // Forward
	{
		Velocity.x = Speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // Backward
	{
		Velocity.x = -Speed;
	}


	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // Right
	{
		Velocity.z = Speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // Left
	{
		Velocity.z = -Speed;
	}
}

float Character::AddMovementInput(glm::vec3 Direction)
{
	Velocity.x += Direction.x;
	Velocity.z += Direction.z;
	return 0;
}
