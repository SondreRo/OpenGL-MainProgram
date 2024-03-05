#pragma once

#include <memory>

#include "Component.h"

#include "Transform.h"
#include <vector>
class Actor
{
	//std::vector<std::unique_ptr<Actor>> Children;
	std::vector<std::unique_ptr<Component>> Components;
public:
	Actor();
	~Actor();

	void Update(float deltaTime);



private:
	Transform transform;
};

