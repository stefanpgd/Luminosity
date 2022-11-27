#pragma once
#include <vector>

class Framebuffer
{
public:
	Framebuffer(unsigned int windowWidth, unsigned int windowHeight, bool doDepthTest, int colorBufferAmount);

	void BindBuffer(float clearColor = 0.0f);
	void BindTexture(unsigned int textureSlot = 0, unsigned int colorBufferIndex = 0);

private:
	bool depthTest = true;
	unsigned int FBO; // Frame Buffer Object
	std::vector<unsigned int> FCO; // Frame Color Objects
};