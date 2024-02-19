

#include "Collider.h"

#include "glm/ext/matrix_transform.hpp"

#include "../mesh.h"

void Collider::SetDisplayMesh(Mesh* inMesh)
{
	DisplayMesh = inMesh;
}

glm::mat4 Collider::CalculateMatrix()
{
	glm::mat4 MeshMatrix(1.0f);

	MeshMatrix *= glm::translate(glm::mat4(1.0f), Location);

	MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	MeshMatrix *= glm::scale(glm::mat4(1.0f), Scale);
	glm::vec3 test = MeshMatrix[3];
	return MeshMatrix;
}
