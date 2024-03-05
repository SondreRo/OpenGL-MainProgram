#pragma once
#include <string>

#include <vector>
#include "Vertex.h"

#include "glm/glm.hpp"
#include "Texture.h"

class Model;

using Index = unsigned int;

class Mesh
{
private:
	int meshMemoryLocation;
	std::string Name;
	std::vector<Texture> textures;
public:

	unsigned int VBO, VAO, EBO;
	Mesh();
	Mesh(std::vector<Vertex> Vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	std::vector<Vertex> vertices;
	std::vector<Index> indices;


	void Bind(unsigned int ShaderProgram);

	void Draw();

	void CleanUp();

	std::string GetName();
	void SetName(std::string NewName);
};

