#pragma once

#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

//class aiScene;
//class aiNode;
//class aiMesh;
//class aiMaterial;
//class aiTextureType;

class Texture;
class Mesh;

class ModelLoader
{
	std::string directory;
public:
	ModelLoader(std::string path);

	void LoadModel(std::string path);

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	unsigned int TextureFromFile(std::string path, std::string directory);
};

