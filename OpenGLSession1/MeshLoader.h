#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

#include "mesh.h"

class MeshLoader
{
	std::vector<Texture> textures_loaded;
	std::string directory;
	Mesh* LastLoadedMesh;
public:
	MeshLoader() = default;

	Mesh* LoadMesh(std::string path, unsigned int shaderProgram);

	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	unsigned int TextureFromFile(std::string path);

	std::vector<Mesh*> Meshes;

};

