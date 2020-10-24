#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <iostream>

struct SDL_Surface;

class Texture
{
public:

	Texture();

	void Load( const char* TextureFileName );
	void SetTextureBuffers();
	GLuint GetCompiledTexture() const;
	bool IsTextureReady() const;

private:

	SDL_Surface*		SurfaceTexture;
	GLuint				CompiledTexture;
};