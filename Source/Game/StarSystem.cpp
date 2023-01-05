#include "StarSystem.h"
#include "Star.h"
#include "Planet.h"

#include <imgui.h>

StarSystem::StarSystem()
{
	systemName = "System - A";

	GenerateSystem();
}

void StarSystem::Update(float deltaTime)
{
	float simulationSpeed = deltaTime * simulationSpeedModifier;

	star->Update(simulationSpeed);

	for(Planet* planet : planets)
	{
		planet->Update(simulationSpeed);
	}
}

void StarSystem::Draw(Camera* camera)
{
	star->Draw(camera);

	for(Planet* planet : planets)
	{
		planet->Draw(camera);
	}

	ImGuiDebugDraw();
}

void StarSystem::GenerateSystem()
{
	star = new Star();

	planets.push_back(new Planet(star));
}

void StarSystem::ImGuiDebugDraw()
{
	ImGui::Begin("System Settings");
	ImGui::DragFloat("Simulation Speed ( Days Per Second )", &simulationSpeedModifier, 0.05f, 0.01f, 100.0f);
	ImGui::End();
}