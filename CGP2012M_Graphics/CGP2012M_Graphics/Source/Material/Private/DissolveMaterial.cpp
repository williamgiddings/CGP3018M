#include <glm/gtc/type_ptr.hpp>

#include <Material/Public/DissolveMaterial.h>
#include <Texture/Public/Texture.h>

DissolveMaterial::DissolveMaterial()
	: NoiseThreshold( 0.0f )
{
	SetShaders();
	SetTextures();
	SetMaterialBuffers();
}

void DissolveMaterial::BindTextureUniforms()
{
	auto FirstTextureLocation = glGetUniformLocation( GetCompiledShader(), "uFirstTexture" );
	glUniform1i( FirstTextureLocation, 0 );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, StoredTextures[0].GetCompiledTexture() );

	auto SecondTextureLocation = glGetUniformLocation( GetCompiledShader(), "uSecondTexture" );
	glUniform1i( SecondTextureLocation, 1 );

	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, StoredTextures[1].GetCompiledTexture() );

	auto NoiseTextureLocation = glGetUniformLocation( GetCompiledShader(), "uNoiseTexture" );
	glUniform1i( NoiseTextureLocation, 2 );

	glActiveTexture( GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, StoredTextures[2].GetCompiledTexture() );

	auto DissolveThresholdLocation = glGetUniformLocation( GetCompiledShader(), "uDissolveThreshold" );
	glUniform1f( DissolveThresholdLocation, NoiseThreshold );

}

void DissolveMaterial::SetNoiseThreshold( const float InThreshold )
{
	NoiseThreshold = InThreshold;
}

void DissolveMaterial::SetMaterialBuffers()
{
	for ( auto& TexturePtr : StoredTextures )
	{
		TexturePtr.SetTextureBuffers();
	}
}

void DissolveMaterial::SetShaders()
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

void DissolveMaterial::SetTextures()
{
	StoredTextures.push_back( Texture( "rock.png" ) );
	StoredTextures.push_back( Texture( "wood.png" ) );
	StoredTextures.push_back( Texture( "noise.png" ) );
}
