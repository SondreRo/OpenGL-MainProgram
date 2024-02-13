#pragma once
#include <vector>

#include "Vertex.h"
#include "glm/glm.hpp"

class Line
{
	unsigned int VBO, VAO;
	unsigned int modelMemoryLocation;
public:
	Line();
	std::vector<Vertex> mVertices;
	void Bind(unsigned int ShaderProgram);
	void Draw();


	glm::vec3 ModelLocation;
	glm::vec3 ModelRotation;
	glm::vec3 ModelScale;


	glm::mat4 CalculateMeshMatrix();
	void Cleanup();

};

