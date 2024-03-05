#pragma once
#include "AppManager.h"
#include "glm/glm.hpp"
class Camera
{
private:
	AppManager* appManager;
	unsigned int viewMemoryLocation;
	unsigned int projectionlLocation;

	float yaw = 90;
	float pitch = 0;
	float roll = 0;

	float Zoom = 45.0f;

	// CameraLocation
	glm::vec3 WorldLocation = glm::vec3(0.0f, 2.0f, -5.0f);
	glm::vec3 LocalLocation = glm::vec3(-5.0f, 3.0f, 0.0f); // Start Position
	
	// CameraRotation
	glm::vec3 LocalRotation = glm::vec3(0,0.0f,0.0f);

	
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::vec3(0.1f,0.0f,0.0f);

	float cameraSpeed = 2.5f;

	glm::vec3 cameraDirection = glm::vec3(0.0f, 1.0f, 0.0f);;


	float lastX = 400, lastY = 300;
	bool firstMouse = true;
public:
	//Camera();
	Camera(unsigned int inShaderProgram, AppManager* inAppManager);
	void AddShaderProgramPath(unsigned int inShaderProgram);
	void AddAppManager(AppManager* inAppManager);
	void tick(float DeltaTime);
	void AddMovement(glm::vec3 Direction, float Speed);
	void AddRotation(float mouseX, float mouseY);
	void HandleInput(struct GLFWwindow *window);
	
	glm::vec3 GetForwardVector();
	glm::vec3 GetRightVector();
	glm::vec3 GetUpVector();
	
	void SetLocation(glm::vec3 NewLocation);
	glm::vec3 GetLocation();
	
	void SetSpeed(float newSpeed);
	float GetSpeed();

};

