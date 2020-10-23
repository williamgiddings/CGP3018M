#include <Mesh\Public\Mesh.h>

Mesh::Mesh( std::vector<float> InVerticies, std::vector<unsigned int> InIndicies, VertexLoadingModes LoadingMode )
	: Verticies( InVerticies )
	, Indicies( InIndicies )
	, VertexLoadingMode( LoadingMode )
{
	VertexShader.shaderFileName( "..//Assets//Shaders//shader_projection.vert" );
	FragmentShader.shaderFileName( "..//Assets//Shaders//shader_projection.frag" );

	VertexShader.getShader( 1 );
	FragmentShader.getShader( 2 );

	CompiledShader = glCreateProgram();
	glAttachShader( CompiledShader, VertexShader.shaderID );
	glAttachShader( CompiledShader, FragmentShader.shaderID );
	glLinkProgram( CompiledShader );

	glDeleteShader( VertexShader.shaderID );
	glDeleteShader( FragmentShader.shaderID );
}

void Mesh::SetTexture( const char * texturePath )
{
	
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

void Mesh::Render()
{
	glUseProgram( CompiledShader );
	glEnable( GL_BLEND );
	glCullFace( GL_BACK );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	if ( !ClearDepth )
	{
		glDisable( GL_DEPTH_TEST );

	}

	glBindVertexArray( VertexArrayObject );
	if ( IsTextureLoaded )
	{
		//glBindTexture(GL_TEXTURE_2D, tex.texture);
	}

	glPointSize( 5.0f );
	if ( RenderWireframe )
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}
	if ( VertexDrawMode == VertexDrawModes::Quads )
	{
		if ( VertexLoadingMode == VertexLoadingModes::Indexed )
		{
			glDrawElements( GL_QUADS, Indicies.size(), GL_UNSIGNED_INT, 0 );
		}
		else
		{
			glDrawArrays( GL_QUADS, 0, Verticies.size() );
		}

	}
	else
	{
		if ( VertexLoadingMode == VertexLoadingModes::Indexed )
		{
			glDrawElements( GL_TRIANGLES, Indicies.size(), GL_UNSIGNED_INT, 0 );
		}
		else
		{
			glDrawArrays( GL_TRIANGLES, 0, Verticies.size() );
		}
	}

	glBindTexture( GL_TEXTURE_2D, 0 );
	glBindVertexArray( 0 );
}
