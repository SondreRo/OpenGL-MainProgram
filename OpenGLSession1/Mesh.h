#pragma once
#include <string>

#include "Vertex.h"
#include "Triangle.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
class Mesh
{
private:
	int modelMemoryLocation;
	std::string Name;
public:
	unsigned int VBO, VAO, EBO;
	Mesh();
	std::vector<Vertex> vertices;
	std::vector<Triangle> indices;

	void Bind(unsigned int ShaderProgram);
	void Draw();
	void CleanUp();

	glm::vec3 ModelLocation;
	glm::vec3 ModelRotation;
	glm::vec3 ModelScale;


	glm::mat4 CalculateMeshMatrix();

	std::string GetName();
	void SetName(std::string NewName);


	void SetLocation(glm::vec3 NewLocation);
	void AddLocation(glm::vec3 AddLocation);
	glm::vec3 GetLocation();

	void SetRotation(glm::vec3 NewRotation);
	void AddRotation(glm::vec3 AddRotation);
	glm::vec3 GetRotation();

	void SetScale(glm::vec3 NewScale);
	void AddScale(glm::vec3 AddScale);
	glm::vec3 GetScale();

};

