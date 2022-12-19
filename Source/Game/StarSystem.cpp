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
}

void StarSystem::Draw(Camera* camera)
{
	star->Draw(camera);
}

void StarSystem::GenerateSystem()
{
	star = new Star();
}