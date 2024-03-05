#pragma once
#include <vector>
#include <windows.h>

#include "Character.h"
#include "Model.h"

class Camera;

class AppManager
{
    float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	unsigned int SCR_WIDTH = 1920;
	unsigned int SCR_HEIGHT = 1080;


	std::vector<Model*> Models;
	
	
public:

	AppManager();

	Model* SelectedModel;
	Character* CurrentCharacter;
	Camera* myCamera;
	void Setup(unsigned int ShaderProgram);
	void ModelSetup(unsigned int ShaderProgram);
	
	void Update();
	void Tick();
	void Draw();
	void CleanUp();

	void HandleInput(struct GLFWwindow* window);

	float GetDeltaTime();

	void SetScreenSize(unsigned int Width, unsigned int Height);
	void GetScreenSize(unsigned int* Width, unsigned int* Height);


	void AddModel(Model* NewModel);

	Model* GetClosestModel();
};
