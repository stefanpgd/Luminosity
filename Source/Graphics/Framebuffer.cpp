#include "Framebuffer.h"
#include <glad/glad.h>

Framebuffer::Framebuffer(unsigned int windowWidth, unsigned int windowHeight, bool doDepthTest)
{
	depthTest = doDepthTest;

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &FTO);
	glBindTexture(GL_TEXTURE_2D, FTO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FTO, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::BindBuffer(float clearColor)
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glClearColor(clearColor, clearColor, clearColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if(depthTest)
	{
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
	} 
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

void Framebuffer::BindTexture(unsigned int textureSlot)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, FTO);
}