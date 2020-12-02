#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <iostream>

struct SDL_Surface;
class Texture
{
public:

	Texture();
	Texture( const char* TextureName, const bool AutoLoad = true );

	void Load( const char* TextureFileName );
	void SetTextureBuffers();
	GLuint GetCompiledTexture() const;
	SDL_Surface* GetSurfaceTexture() const;

private:

	SDL_Surface*		SurfaceTexture;
	GLuint				CompiledTexture;
};