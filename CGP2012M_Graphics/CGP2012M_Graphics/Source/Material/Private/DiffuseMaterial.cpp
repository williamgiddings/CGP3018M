#include <glm/gtc/type_ptr.hpp>

#include <Material/Public/DiffuseMaterial.h>
#include <Texture/Public/Texture.h>

DiffuseMaterial::DiffuseMaterial()
{
	SetShaders();
	SetTextures();
	SetMaterialBuffers();
}

void DiffuseMaterial::BindTextureUniforms()
{
	auto FirstTextureLocation = glGetUniformLocation( GetCompiledShader(), "uFirstTexture" );
	glUniform1i( FirstTextureLocation, 0 );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, StoredTextures[0].GetCompiledTexture() );

	auto SecondTextureLocation = glGetUniformLocation( GetCompiledShader(), "uSecondTexture" );
	glUniform1i( SecondTextureLocation, 1 );

	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, StoredTextures[1].GetCompiledTexture() );

}

void DiffuseMaterial::SetMaterialBuffers()
{
	for ( auto& TexturePtr : StoredTextures )
	{
		TexturePtr.SetTextureBuffers();
	}
}

void DiffuseMaterial::SetShaders()
{
	VertexShader.SetShaderProgram( Shader::ShaderType::Vertex, "shaderNew" );
	FragmentShader.SetShaderProgram( Shader::ShaderType::Fragment, "shaderNew" );

	CompiledShader = glCreateProgram();
	glAttachShader( CompiledShader, VertexShader.GetCompiledShader() );
	glAttachShader( CompiledShader, FragmentShader.GetCompiledShader() );
	glLinkProgram( CompiledShader );

	glDeleteShader( VertexShader.GetCompiledShader() );
	glDeleteShader( FragmentShader.GetCompiledShader() );
}

void DiffuseMaterial::SetTextures()
{
	StoredTextures.push_back( Texture( "rock.png" ) );
	StoredTextures.push_back( Texture( "wood.png" ) );
}
