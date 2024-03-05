#pragma once
#include "Mesh.h"
#include <vector>
#include <string>

#include "glm/glm.hpp"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

class Mesh;

class Model
{
	glm::vec3 ModelLocation = glm::vec3(0);
	glm::vec3 ModelRotation = glm::vec3(0);
	glm::vec3 ModelScale = glm::vec3(1);

	unsigned int modelMemoryLocation;
	std::string Name;


	std::vector<Texture> textures_loaded;
	std::string directory;
	
public:
	Model();
	std::vector<Mesh*> Meshes;
	glm::vec3 Velocity;
	glm::mat4 CalculateMeshMatrix();

	// Transform
	void SetLocation(glm::vec3 NewLocation);
	void AddLocation(glm::vec3 AddLocation);
	glm::vec3 GetLocation();
	
	void SetRotation(glm::vec3 NewRotation);
	void AddRotation(glm::vec3 AddRotation);
	inline glm::vec3 GetRotation() { return ModelRotation; }
	
	void SetScale(glm::vec3 NewScale);
	void AddScale(glm::vec3 AddScale);
	inline glm::vec3 GetScale() { return ModelScale; }

	
	virtual void Tick(float DeltaTime);
	virtual void Draw();
	virtual void CollisionResponce(Mesh* OwnMesh, Mesh* OtherMesh, Model* OtherModel);
	virtual void HandleInput(struct GLFWwindow* window);


	// Extra
	void CleanUp();
	void Setup(unsigned int ShaderProgram);
	
	std::string GetName();
	void SetName(std::string NewName);

	void AddMesh(Mesh* NewMesh);

	void LoadModel(std::string path);

	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	unsigned int TextureFromFile(std::string path, std::string directory);

	//std::string directory;

	bool IsVisible = true;
	bool IsCollisionDisabled = false;
};
