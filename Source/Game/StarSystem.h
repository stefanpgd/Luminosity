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

	// System Objects // 
	Star* star;

	// System Info // 
	std::string systemName;

	// System Settings // 
	float simulationSpeed = 1.0f;
	bool sidePerspective = false;
};