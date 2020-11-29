#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <Engine/EngineEnvironment.h>
#include <Texture/Public/Texture.h>

Texture::Texture()
	: Texture( "", false )
{
}

Texture::Texture( const char* TextureName, const bool AutoLoad )
	: SurfaceTexture()
	, CompiledTexture()
{
	if ( AutoLoad )
	{
		Load( TextureName );
	}
}

void Texture::Load( const char* TextureFileName )
{
	const std::string TexturePath = EngineEnvironment::TextureDir + std::string( TextureFileName );

	SurfaceTexture = IMG_Load( TexturePath.c_str() );

	if ( SurfaceTexture == NULL )
	{
		std::cout << "Error loading CompiledTexture: " << TextureFileName << std::endl;
	}
	else
	{
		std::cout << "Success loading " << TextureFileName << std::endl;
	}
}

void Texture::SetTextureBuffers()
{
	glGenTextures( 1, &CompiledTexture );

	glBindTexture( GL_TEXTURE_2D, CompiledTexture );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		SurfaceTexture->w,
		SurfaceTexture->h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		SurfaceTexture->pixels
	);

	glBindTexture( GL_TEXTURE_2D, 0 );
	SDL_FreeSurface( SurfaceTexture );
}

GLuint Texture::GetCompiledTexture() const
{
	return CompiledTexture;
}

SDL_Surface* Texture::GetSurfaceTexture() const
{
	return SurfaceTexture;
}
