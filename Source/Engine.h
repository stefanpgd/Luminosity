#pragma once

class Renderer;

class Engine
{
public:
	Engine();

	void Run();

private:
	Renderer* renderer;
};