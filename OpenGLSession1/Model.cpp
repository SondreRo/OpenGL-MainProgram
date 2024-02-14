#include "Model.h"

#include <iostream>

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

void Model::LoadModel(std::string path)
{
	Assimp::Importer importer;
	unsigned int processFlags =
		aiProcess_CalcTangentSpace | // calculate tangents and bitangents if possible
		aiProcess_JoinIdenticalVertices | // join identical vertices/ optimize indexing
		aiProcess_ValidateDataStructure  | // perform a full validation of the loader's output
		aiProcess_Triangulate | // Ensure all verticies are triangulated (each 3 vertices are triangle)
		//aiProcess_ConvertToLeftHanded | // convert everything to D3D left handed space (by default right-handed, for OpenGL)
		aiProcess_SortByPType | // ?
		aiProcess_ImproveCacheLocality | // improve the cache locality of the output vertices
		aiProcess_RemoveRedundantMaterials | // remove redundant materials
		aiProcess_FindDegenerates | // remove degenerated polygons from the import
		aiProcess_FindInvalidData | // detect invalid model data, such as invalid normal vectors
		aiProcess_GenUVCoords | // convert spherical, cylindrical, box and planar mapping to proper UVs
		aiProcess_TransformUVCoords | // preprocess UV transformations (scaling, translation ...)
		aiProcess_FindInstances | // search for instanced meshes and remove them by references to one master
		aiProcess_LimitBoneWeights | // limit bone weights to 4 per vertex
		aiProcess_OptimizeMeshes | // join small meshes, if possible;
		aiProcess_PreTransformVertices | //-- fixes the transformation issue.
		aiProcess_SplitByBoneCount | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader
		aiProcess_FlipUVs |
		0;

	//const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	const aiScene* scene = importer.ReadFile(path, processFlags);


	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;
		// Position
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// Normal
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		// TextureCoordinates
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	Mesh* NewMesh = new Mesh(vertices, indices, textures);
	return NewMesh; //Return the mesh
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
		}
	}
	return textures;
}

unsigned int Model::TextureFromFile(std::string path, std::string directory)
{
	stbi_set_flip_vertically_on_load(false);
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	//unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);TestMaterial.png
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
