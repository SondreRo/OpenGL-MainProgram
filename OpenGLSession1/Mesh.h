#pragma once
#include <string>

#include <vector>
#include "Vertex.h"
#include "Triangle.h"

#include "glm/glm.hpp"

#include "Collisions.h"

//#include "Vertex.h"
//#include "Triangle.h"
//#include <vector>
//#include <glm/glm.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include "Collisions.h"

class Mesh
{
private:
	int meshMemoryLocation;
	std::string Name;
public:

	Model* Owner;
	unsigned int VBO, VAO, EBO;
	Mesh();
	std::vector<Vertex> vertices;
	std::vector<Triangle> indices;

	void Bind(unsigned int ShaderProgram);
	void Draw();
	void CleanUp();

	glm::vec3 MeshLocation;
	glm::vec3 MeshRotation;
	glm::vec3 MeshScale;


	glm::mat4 CalculateMeshMatrix();

	std::string GetName();
	void SetName(std::string NewName);

	Model* GetOwner();

	void SetLocation(glm::vec3 NewLocation);
	void AddLocation(glm::vec3 AddLocation);
	glm::vec3 GetLocation();

	void SetRotation(glm::vec3 NewRotation);
	void AddRotation(glm::vec3 AddRotation);
	glm::vec3 GetRotation();

	void SetScale(glm::vec3 NewScale);
	void AddScale(glm::vec3 AddScale);
	glm::vec3 GetScale();

	std::vector<SphereCollider*> SphereColliders;
	void AddSphereCollider(glm::vec3 Center, float Radius);

	std::vector<SphereCollider*> GetSphereColliders();
};

