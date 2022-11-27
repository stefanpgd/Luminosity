#pragma once

class Framebuffer
{
public:
	Framebuffer(unsigned int windowWidth, unsigned int windowHeight, bool doDepthTest);

	void BindBuffer(float clearColor = 0.0f);
	void BindTexture(unsigned int textureSlot = 0);

private:
	bool depthTest = true;
	unsigned int FBO; // Frame Buffer Object
	unsigned int FTO; // Frame Texture Object
};