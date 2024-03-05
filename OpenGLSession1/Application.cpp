#include "Application.h"

#include "Actor.h"

void Application::Update(float deltaTime)
{
	for (const auto & actor : Actors)
	{
		actor->Update(deltaTime);
	}
}

void Application::Render()
{

}
