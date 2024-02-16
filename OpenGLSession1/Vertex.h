#pragma once
#include <vector>
#include "glm/glm.hpp"
class Vertex
{
public:
	Vertex() = default;
	Vertex(glm::vec3 Loc)
	{
		Position = Loc;

	}
	
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
