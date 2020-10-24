
#include <SDL_image.h>
#include <Texture\Public\Texture.h>

Texture::Texture()
	: SurfaceTexture()
	, CompiledTexture()
{
}

void Texture::Load( const char* TextureFileName )
{
	SurfaceTexture = IMG_Load( TextureFileName );

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

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	glTexImage2D( GL_TEXTURE_2D,
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

bool Texture::IsTextureReady() const
{
	return SurfaceTexture;
}
