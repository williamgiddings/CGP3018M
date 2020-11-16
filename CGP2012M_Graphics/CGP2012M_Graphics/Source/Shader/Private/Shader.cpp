#include <Shader/Public/Shader.h>
#include <Engine/EngineEnvironment.h>

Shader::Shader()
	: RawShaderProgram()
	, ShaderProgramData()
	, CompiledShader()
{
}

const std::string Shader::GetShaderExtensionFromType( const ShaderType InShaderType ) const
{
	return InShaderType == ShaderType::Fragment ? ".frag" : ".vert";
}

void Shader::SetShaderProgram( const ShaderType InShaderType, std::string InShaderName )
{
	const std::string ShaderFilePath = InShaderName + GetShaderExtensionFromType( InShaderType );
	ShaderProgramData = GetShaderProgram( ShaderFilePath );
	RawShaderProgram = ShaderProgramData.c_str();

	switch ( InShaderType )
	{
		case ShaderType::Vertex:
			CompiledShader = glCreateShader( GL_VERTEX_SHADER );
			break;
		case ShaderType::Fragment:
			CompiledShader = glCreateShader( GL_FRAGMENT_SHADER );
			break;
	}

	glShaderSource( CompiledShader, 1, &RawShaderProgram, NULL );
	glCompileShader( CompiledShader );

	//debug shader compile
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv( CompiledShader, GL_COMPILE_STATUS, &success );
	std::cout << "Shader compile: " << CompiledShader << " " << success << std::endl;

	if ( !success )
	{
		glGetShaderInfoLog( CompiledShader, 512, NULL, infoLog );
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

}

GLuint Shader::GetCompiledShader() const
{
	return CompiledShader;
}

std::string Shader::GetShaderProgram( std::string ShaderName )
{
	const auto ShaderFilePath = EngineEnvironment::ShaderDir + ShaderName;
	std::ifstream inFile( ShaderFilePath.c_str() );
	std::string ShaderProgramData;

	while ( inFile.good() )
	{
		std::string line;
		std::getline( inFile, line );
		ShaderProgramData.append( line + "\n" );
	}
	const bool ValidShader = ShaderProgramData.length() > 0;

	std::cout << ( ValidShader ? "import success:" : "import failed:") << std::endl;
	return ShaderProgramData;
}
