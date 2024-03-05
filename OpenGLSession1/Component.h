#pragma once
#include "Transform.h"
#include <memory>

class Actor;

class Component
{
public:
	Component();

	void Update(float deltaTime);

private:
	Transform transform;
	std::shared_ptr<Actor> ParentActor;
};

