#include <Mesh/Public/MeshInstance.h>

MeshInstance::MeshInstance()
	: MeshInstance( nullptr )
{
}

MeshInstance::MeshInstance( std::shared_ptr<Mesh> PooledMeshReference )
	: ObjectMesh( PooledMeshReference )
	, VertexShader()
	, FragmentShader()
	, RenderWireframe( false )
	, FlipUVs( false )
	, ClearDepth( true )
	, MeshBuffersSet( false )
	, VertexDrawMode( MeshInstance::VertexDrawModes::Tris )
	, CompiledShader()
{
	VertexShader.SetShaderProgram( Shader::ShaderType::Vertex, "shader" );
	FragmentShader.SetShaderProgram( Shader::ShaderType::Fragment, "shader" );

	CompiledShader = glCreateProgram();
	glAttachShader( CompiledShader, VertexShader.GetCompiledShader() );
	glAttachShader( CompiledShader, FragmentShader.GetCompiledShader() );
	glLinkProgram( CompiledShader );

	glDeleteShader( VertexShader.GetCompiledShader() );
	glDeleteShader( FragmentShader.GetCompiledShader() );
}

void MeshInstance::SetRenderType( const VertexDrawModes DrawMode )
{
	VertexDrawMode = DrawMode;
}

void MeshInstance::ApplyRenderSettings()
{
	if ( ObjectMesh )
	{
		glUseProgram( CompiledShader );
		glEnable( GL_BLEND );
		glCullFace( GL_BACK );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable( GL_DEPTH_TEST );
		glDepthFunc( GL_LEQUAL );
		glBindVertexArray( ObjectMesh->GetVertexArrayObject() );
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
}

void MeshInstance::ApplyTextures()
{
	if ( ObjectMesh )
	{
		const Texture& const MeshTexture = ObjectMesh->GetMeshTexture();

		if ( MeshTexture.IsTextureReady() )
		{
			glBindTexture( GL_TEXTURE_2D, MeshTexture.GetCompiledTexture() );
		}
	}	
}

void MeshInstance::Render()
{
	if ( ObjectMesh )
	{
		const auto& Verticies = ObjectMesh->GetVerticies();
		const auto& Indicies = ObjectMesh->GetIndicies();
		
		ObjectMesh->SetMeshBuffers();
		ApplyRenderSettings();
		ApplyTextures();

		switch ( ObjectMesh->GetVertexReadMode() )
		{
			case Mesh::VertexLoadingModes::Indexed:
				glDrawElements( VertexDrawMode, Indicies.size(), GL_UNSIGNED_INT, 0 );
				break;
			case Mesh::VertexLoadingModes::Array:
				glDrawArrays( VertexDrawMode, 0, Verticies.size() );
				break;
			default:
				break;
		}

		glBindTexture( GL_TEXTURE_2D, 0 );
		glBindVertexArray( 0 );
	}
}
