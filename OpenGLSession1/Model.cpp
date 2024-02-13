#include "Model.h"

#include "AppManager.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

Model::Model()
{
	modelMemoryLocation = -1;
}

glm::mat4 Model::CalculateMeshMatrix()
{
	glm::mat4 MeshMatrix(1.0f);

	MeshMatrix *= glm::translate(glm::mat4(1.0f), ModelLocation);

	MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(ModelRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(ModelRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(ModelRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	MeshMatrix *= glm::scale(glm::mat4(1.0f), ModelScale);

	return MeshMatrix;
}

void Model::SetLocation(glm::vec3 NewLocation)
{
	ModelLocation = NewLocation;
}

void Model::AddLocation(glm::vec3 AddLocation)
{
	ModelLocation += AddLocation;
}

glm::vec3 Model::GetLocation()
{
	return ModelLocation;
}

void Model::SetRotation(glm::vec3 NewRotation)
{
	ModelRotation = NewRotation;
}

void Model::AddRotation(glm::vec3 AddRotation)
{
	ModelRotation += AddRotation;
}

void Model::SetScale(glm::vec3 NewScale)
{
	ModelScale = NewScale;
}

void Model::AddScale(glm::vec3 AddScale)
{
	ModelScale += AddScale;
}

void Model::Tick(float DeltaTime)
{
	
}

void Model::Draw()
{
	glUniformMatrix4fv(modelMemoryLocation, 1, GL_FALSE, glm::value_ptr(CalculateMeshMatrix()));
	for (auto Mesh : Meshes)
	{
		Mesh->Draw();
	}
}

void Model::CleanUp()
{
	for (auto Mesh : Meshes)
	{
		Mesh->CleanUp();
	}
}

void Model::Setup(unsigned int ShaderProgram)
{
	modelMemoryLocation = glGetUniformLocation(ShaderProgram, "model");
	for (auto mesh : Meshes)
	{
		mesh->Bind(ShaderProgram);
	}
}

std::string Model::GetName()
{
	return Name;
}

void Model::SetName(std::string NewName)
{
	Name = NewName;
}

void Model::AddMesh(Mesh* NewMesh)
{
	NewMesh->Owner = this;
	Meshes.push_back(NewMesh);
}

std::vector<SphereCollider*> Model::GetSphereColliders()
{
	std::vector<SphereCollider*> SphereCollidersToReturn;
	if(Meshes.empty())
	{
		return SphereCollidersToReturn;
	}
	for (auto Mesh : Meshes)
	{
		for (auto sphere_collider : Mesh->GetSphereColliders())
		{
			SphereCollidersToReturn.push_back(sphere_collider);
		}
	}
	return SphereCollidersToReturn;
}
