#pragma once
#include <string>

#include <vector>
#include "Vertex.h"

#include "glm/glm.hpp"
#include "Texture.h"
#include "Collision/AxisAlignedBoundingBox.h"

#include "Collision/SphereCollider.h"

class Model;

class Mesh
{
private:
	int meshMemoryLocation;
	std::string Name;
	std::vector<Texture> textures;
public:

	Model* Owner;
	unsigned int VBO, VAO, EBO;
	Mesh();
	Mesh(std::vector<Vertex> Vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;


	void Bind(unsigned int ShaderProgram);

	void Draw();
	void Draw(glm::mat4 ParentMat);

	void CleanUp();

	glm::vec3 MeshLocation{ 0.0f };
	glm::vec3 MeshRotation{ 0.0f };
	glm::vec3 MeshScale{ 1 };


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

	glm::vec3 CalculateCenter();
	glm::vec3 CalculateScale();



	std::vector<SphereCollider*> SphereColliders;

	void AddSphereCollider(glm::vec3 Location, float Radius);
	void AddSphereCollider(glm::vec3 Location, float Radius, Mesh* DisplayMesh);

	std::vector<AxisAlignedBoundingBox*> AxisAlignedBoundingBoxColliders;

	void AddAxisAlignedBoundingBoxCollider(glm::vec3 Location, glm::vec3 Scale);
	void AddAxisAlignedBoundingBoxCollider(glm::vec3 Location, glm::vec3 Scale, Mesh* DisplayMesh);
	void AddAxisAlignedBoundingBoxColliderAuto(Mesh* DisplayMesh);
};

