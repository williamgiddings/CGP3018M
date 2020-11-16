#pragma once
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

class Shader
{
public:

	enum class ShaderType
	{
		Vertex,
		Fragment
	};

public:

	Shader();

	void SetShaderProgram( const ShaderType InShaderType, std::string InShaderName );
	GLuint GetCompiledShader() const;
	
	const std::string GetShaderExtensionFromType( const ShaderType InShaderType ) const;

private:

	std::string GetShaderProgram( std::string ShaderName );

private:
	
	const char*		RawShaderProgram;
	std::string		ShaderProgramData;
	GLuint			CompiledShader;
};

