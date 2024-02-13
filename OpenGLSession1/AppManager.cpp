#include "AppManager.h"

#include "GLFW/glfw3.h"
#include <iostream>
#include "Camera.h"
#include "Collisions.h"

AppManager::AppManager()
{
	SelectedModel = nullptr;
	myCamera = nullptr;
}

void AppManager::ModelSetup(unsigned ShaderProgram)
{
	for (auto& Model : Models)
	{
		Model->Setup(ShaderProgram);
	}
}

void AppManager::Update()
{
	const float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void AppManager::Tick()
{
	if(SelectedModel)
	{
		//myCamera->SetLocation(SelectedModel->GetLocation());
	}
	for (auto& Model : Models)
	{
		Model->Tick(deltaTime);
		Model->Draw();
		for (auto& Model2 : Models)
		{
			if (Model != Model2)
			{
				CollisionResult collisionResult = Collisions::CheckSphereCollisions(Model, Model2);
				if(collisionResult.IsColliding)
				{
					std::cout << collisionResult.MainModel->GetName() << " " << collisionResult.OtherModel->GetName() << std::endl;
					collisionResult.OtherModel->AddScale(glm::vec3(-0.001f));
					collisionResult.MainModel->AddScale(glm::vec3(-0.001f));
				}
			}
		}
	}
}

void AppManager::CleanUp()
{
	for (auto& Model : Models)
	{
		Model->CleanUp();
	}
}

float AppManager::GetDeltaTime()
{
	return deltaTime;
}

void AppManager::SetScreenSize(unsigned Width, unsigned Height)
{
	SCR_WIDTH = Width;
	SCR_HEIGHT = Height;
}

void AppManager::GetScreenSize(unsigned* Width, unsigned* Height)
{
	*Width = SCR_WIDTH;
	*Height = SCR_HEIGHT;
}

void AppManager::AddModel(Model* NewModel)
{
	Models.push_back(NewModel);
}

Model* AppManager::GetClosestModel()
{
	if(Models.empty())
	{
		std::cout << "No models in AppManager" << std::endl;
		return nullptr;
	}
	
	float ClosestDistance = 100000000;
	Model* ClosestModel = Models[0];
	
	for (auto model : Models)
	{
		float currentDistance = glm::distance(myCamera->GetLocation(), model->GetLocation());
		if (currentDistance < ClosestDistance)
		{
			ClosestModel = model;
			ClosestDistance = currentDistance;
		}
	}
	SelectedModel = ClosestModel;
	return ClosestModel;

}
