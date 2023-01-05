#pragma once
#include <vector>
#include <string>

class Star;
class Planet;
class Camera;

class StarSystem
{
public:
	StarSystem();

	void Update(float deltaTime);
	void Draw(Camera* camera);

private:
	void GenerateSystem();
	void ImGuiDebugDraw();

	// System Objects // 
	Star* star;
	std::vector<Planet*> planets;

	// System Info // 
	std::string systemName;

	// System Settings // 
	float simulationSpeedModifier = 1.0f;
	bool sidePerspective = false;
};