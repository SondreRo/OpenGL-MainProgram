#include "AxisAlignedBoundingBox.h"

#include "../Mesh.h"
#include "glm/ext/matrix_transform.hpp"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(glm::vec3 inLocation, glm::vec3 inScale)
{
	Location = inLocation;
	Scale = inScale;
}

glm::vec3 AxisAlignedBoundingBox::GetCenter()
{
	return Location;
}

glm::vec3 AxisAlignedBoundingBox::GetScale()
{
	return Scale;
}

glm::mat4 AxisAlignedBoundingBox::CalculateMatrix()
{
	glm::mat4 MeshMatrix(1.0f);

	MeshMatrix *= glm::translate(glm::mat4(1.0f), Location);

	MeshMatrix *= glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(1.0f, 0.0f, 0.0f));
	MeshMatrix *= glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(0.0f, 1.0f, 0.0f));
	MeshMatrix *= glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(0.0f, 0.0f, 1.0f));

	MeshMatrix *= glm::scale(glm::mat4(1.0f), Scale);
	glm::vec3 test = MeshMatrix[3];

	return MeshMatrix;
}

void AxisAlignedBoundingBox::DrawDisplayMesh()
{
	if (DisplayMesh)
	{
		
		DisplayMesh->Draw(CalculateMatrix());
	}
}
