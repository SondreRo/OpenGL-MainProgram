#include "Actor.h"

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Update(float deltaTime)
{
	for (const auto& Component : Components)
	{
		Component->Update(deltaTime);
	}
}