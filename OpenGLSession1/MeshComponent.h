#pragma once
#include "Component.h"
#include "mesh.h"
class MeshComponent : public Component
{
public:
	std::shared_ptr<Mesh> Mesh;
};

