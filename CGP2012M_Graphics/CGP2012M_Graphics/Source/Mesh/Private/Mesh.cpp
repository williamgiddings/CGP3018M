#include <Mesh\Public\Mesh.h>

Mesh::Mesh( std::vector<float> InVerticies, std::vector<unsigned int> InIndicies, VertexLoadingModes LoadingMode )
	: Verticies( InVerticies )
	, UVCoords()
	, Normals()
	, Indicies( InIndicies )
	, MeshTexture()
	, VertexShader()
	, FragmentShader()
	, RenderWireframe( false )
	, FlipUVs( false )
	, VertexLoadingMode( LoadingMode )
	, VertexDrawMode( Mesh::VertexDrawModes::Tris )
	, CompiledShader()
	, VertexBufferObject()
	, VertexArrayObject()
	, IndexBufferObject()
	, ClearDepth( true )
{
	VertexShader.SetShaderProgram( Shader::ShaderType::Vertex, "..//Assets//Shaders//shader_projection.vert" );
	FragmentShader.SetShaderProgram( Shader::ShaderType::Fragment, "..//Assets//Shaders//shader_projection.frag" );

	CompiledShader = glCreateProgram();
	glAttachShader( CompiledShader, VertexShader.GetCompiledShader() );
	glAttachShader( CompiledShader, FragmentShader.GetCompiledShader() );
	glLinkProgram( CompiledShader );

	glDeleteShader( VertexShader.GetCompiledShader() );
	glDeleteShader( FragmentShader.GetCompiledShader() );
}

void Mesh::SetTexture( const char* InTextureFilePath )
{
	MeshTexture.Load( InTextureFilePath );
	MeshTexture.SetTextureBuffers();
}

void Mesh::SetRenderMode( VertexLoadingModes LoadingMode )
{
	VertexLoadingMode = LoadingMode;
}

void Mesh::SetRenderType( const VertexDrawModes DrawMode )
{
	VertexDrawMode = DrawMode;
}

void Mesh::SetMeshBuffers()
{
	//Create Vertex Array Object
	glGenVertexArrays( 1, &VertexArrayObject );
	glBindVertexArray( VertexArrayObject );

	//Create vertex buffer
	glGenBuffers( 1, &VertexBufferObject );
	glBindBuffer( GL_ARRAY_BUFFER, VertexBufferObject );
	glBufferData( GL_ARRAY_BUFFER, Verticies.size() * sizeof( float ), &Verticies[0], GL_STATIC_DRAW );

	//Assign Attributes
	glBindBuffer( GL_ARRAY_BUFFER, VertexBufferObject );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), ( GLvoid* ) 0 );
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), ( GLvoid* ) ( 3 * sizeof( float ) ) );
	glEnableVertexAttribArray( 1 );

	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), ( GLvoid* ) ( 5 * sizeof( float ) ) );
	glEnableVertexAttribArray( 2 );

	//Create index buffer
	if ( VertexLoadingMode == VertexLoadingModes::Indexed )
	{
		glGenBuffers( 1, &IndexBufferObject );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IndexBufferObject );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, Indicies.size() * sizeof( GLuint ), &Indicies[0], GL_STATIC_DRAW );
	}

	glBindVertexArray( 0 );
}

void Mesh::ApplyRenderSettings()
{
	glUseProgram( CompiledShader );
	glEnable( GL_BLEND );
	glCullFace( GL_BACK );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glBindVertexArray( VertexArrayObject );
	glPointSize( 5.0f );

	if ( !ClearDepth )
	{
		glDisable( GL_DEPTH_TEST );
	}

	if ( RenderWireframe )
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}
}

void Mesh::ApplyTextures()
{
	if ( MeshTexture.IsTextureReady() )
	{
		glBindTexture( GL_TEXTURE_2D, MeshTexture.GetCompiledTexture() );
	}
}

void Mesh::Render()
{
	ApplyRenderSettings();
	ApplyTextures();

	switch ( VertexLoadingMode )
	{
		case VertexLoadingModes::Indexed:
			glDrawElements( VertexDrawMode, Indicies.size(), GL_UNSIGNED_INT, 0 );
			break;
		case VertexLoadingModes::Array:
			glDrawArrays( VertexDrawMode, 0, Verticies.size() );
			break;
		default:
			break;	
	}

	glBindTexture( GL_TEXTURE_2D, 0 );
	glBindVertexArray( 0 );
}
