#include <Mesh/Public/Mesh.h>

Mesh::Mesh( std::vector<float> InVerticies, std::vector<unsigned int> InIndicies, VertexLoadingModes LoadingMode )
	: Verticies( InVerticies )
	, UVCoords()
	, Normals()
	, Indicies( InIndicies )
	, VertexBufferObject()
	, IndexBufferObject()
	, VertexArrayObject()
	, MeshTexture()
	, VertexLoadingMode( LoadingMode )
{
	SetMeshBuffers();
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
	if ( GetVertexReadMode() == Mesh::VertexLoadingModes::Indexed )
	{
		glGenBuffers( 1, &IndexBufferObject );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IndexBufferObject );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, Indicies.size() * sizeof( GLuint ), &Indicies[0], GL_STATIC_DRAW );
	}

	glBindVertexArray( 0 );
}

void Mesh::SetLoadingMode( VertexLoadingModes LoadingMode )
{
	VertexLoadingMode = LoadingMode;
}

void Mesh::SetTexture( const char* InTextureFilePath )
{
	MeshTexture.Load( InTextureFilePath );
	MeshTexture.SetTextureBuffers();
}

const Mesh::VertexLoadingModes Mesh::GetVertexReadMode() const
{
	return VertexLoadingMode;
}

const std::vector<float>& Mesh::GetVerticies() const
{
	return Verticies;
}

const std::vector<float>& Mesh::GetUVCoords() const
{
	return UVCoords;
}

const std::vector<float>& Mesh::GetNormals() const
{
	return Normals;
}

const std::vector<GLuint>& Mesh::GetIndicies() const
{
	return Indicies;
}

const Texture& Mesh::GetMeshTexture() const
{
	return MeshTexture;
}

GLuint Mesh::GetVertexBuffer() const
{
	return VertexBufferObject;
}

GLuint Mesh::GetIndexBuffer() const
{
	return IndexBufferObject;
}

GLuint Mesh::GetVertexArrayObject() const
{
	return VertexArrayObject;
}

