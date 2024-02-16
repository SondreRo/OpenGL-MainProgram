#pragma once
#include <vector>

#include "Vertex.h"

class Dots
{
	unsigned int VBO, VAO;
	unsigned int modelMemoryLocation;

public:
	Dots();
	std::vector<Vertex> mVertices;
	void Bind(unsigned int ShaderProgram);
	void Draw();


	glm::vec3 ModelLocation;
	glm::vec3 ModelRotation;
	glm::vec3 ModelScale;


	glm::mat4 CalculateMeshMatrix();
	void Cleanup();

};

