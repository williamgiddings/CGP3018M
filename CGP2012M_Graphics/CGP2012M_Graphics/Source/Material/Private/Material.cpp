#include <GL/glew.h>
#include <SDL_image.h>

#include <Material/Public/Material.h>
#include <Texture/Public/Texture.h>

Material::Material()
	: VertexShader()
	, FragmentShader()
	, CompiledShader()
	, StoredTextures()
{
	SetShaders();
}

void Material::SetMaterialBuffers()
{
}

void Material::SetShaders()
{
}

void Material::BindTextureUniforms()
{
}

void Material::SetTextures()
{
}

GLuint Material::GetCompiledShader() const
{
	return CompiledShader;
}
