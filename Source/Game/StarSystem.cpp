#include "StarSystem.h"
#include "Star.h"
#include "Planet.h"

StarSystem::StarSystem()
{
	systemName = "System - A";

	GenerateSystem();
}

void StarSystem::Update(float deltaTime)
{
	star->Update(deltaTime);

	for(Planet* planet : planets)
	{
		planet->Update(deltaTime);
	}
}

void StarSystem::Draw(Camera* camera)
{
	star->Draw(camera);

	for(Planet* planet : planets)
	{
		planet->Draw(camera);
	}
}

void StarSystem::GenerateSystem()
{
	star = new Star();

	planets.push_back(new Planet(star));
}