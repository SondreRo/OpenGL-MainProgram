#pragma once
#include <memory>
#include <vector>

class Actor;

class Application
{
	std::vector<std::shared_ptr<Actor>> Actors;

	void Update(float deltaTime);
	void Render();
};

