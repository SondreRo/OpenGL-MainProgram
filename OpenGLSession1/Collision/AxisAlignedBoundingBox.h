#pragma once
#include "Collider.h"

class AxisAlignedBoundingBox : public Collider
{
public:
	AxisAlignedBoundingBox(glm::vec3 inLocation, glm::vec3 inScale);
	glm::vec3 GetCenter();
	glm::vec3 GetScale();

	virtual glm::mat4 CalculateMatrix() override;
	virtual void DrawDisplayMesh() override;
};

