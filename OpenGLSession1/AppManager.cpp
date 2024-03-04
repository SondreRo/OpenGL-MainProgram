#include "AppManager.h"

#include "GLFW/glfw3.h"
#include <iostream>
#include "Camera.h"

#include "Collision/CollisionManager.h"


AppManager::AppManager()
{
	SelectedModel = nullptr;
	myCamera = nullptr;
}

void AppManager::Setup(unsigned ShaderProgram)
{
	myCamera = new Camera(ShaderProgram, this);

	ModelSetup(ShaderProgram);
}

void AppManager::ModelSetup(unsigned ShaderProgram)
{
	for (auto& Model : Models)
	{
		Model->Setup(ShaderProgram);
	}


	myCamera->AddShaderProgramPath(ShaderProgram);
}

void AppManager::Update()
{
	const float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void AppManager::CollisionTick()
{
	for (auto Model1 : Models)
	{
		for (auto Model2 : Models)
		{
			if (Model1 != Model2)
			{
				CollisionManager::CheckModelsCollision(Model1, Model2);
			}
		}
	}
}	


void AppManager::Tick()
{
	CollisionTick();
	if(SelectedModel)
	{
		//myCamera->SetLocation(SelectedModel->GetLocation());
	}
	for (auto& Model : Models)
	{
		Model->Tick(deltaTime);
		myCamera->tick(deltaTime);
	}
}

void AppManager::Draw()
{
	for (auto& Model : Models)
	{
		Model->Draw();
	}
}

void AppManager::CleanUp()
{
	for (auto& Model : Models)
	{
		Model->CleanUp();
	}
}

void AppManager::HandleInput(GLFWwindow* window)
{
	myCamera->HandleInput(window);
	for (auto& Model : Models)
	{
		Model->HandleInput(window);
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
