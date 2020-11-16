#include <glm/gtc/type_ptr.hpp>

#include <Mesh/Public/MeshInstance.h>
#include <SceneObject/Public/ScenePhysObject.h>

MeshInstance::MeshInstance()
	: MeshInstance( nullptr, nullptr )
{
}

MeshInstance::MeshInstance( ScenePhysObject* InInstanceOwner, std::shared_ptr<Mesh> PooledMeshReference )
	: ObjectMesh( PooledMeshReference )
	, VertexShader()
	, FragmentShader()
	, RenderWireframe( true )
	, FlipUVs( false )
	, ClearDepth( false )
	, VertexDrawMode( MeshInstance::VertexDrawModes::Tris )
	, CompiledShader()
	, InstanceOwner( InInstanceOwner )
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

void MeshInstance::ApplyShaderUniforms()
{
	GLuint TransformLocation = glGetUniformLocation( CompiledShader, "transform" );
	glm::mat4 Mat = InstanceOwner->GetMatrix();
	glUniformMatrix4fv( TransformLocation, 1, GL_FALSE, glm::value_ptr( Mat ) );
}

void MeshInstance::ApplyRenderSettings()
{
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

void MeshInstance::ApplyTextures()
{
	const Texture& const MeshTexture = ObjectMesh->GetMeshTexture();

	if ( MeshTexture.IsTextureReady() )
	{
		glBindTexture( GL_TEXTURE_2D, MeshTexture.GetCompiledTexture() );
	}
}

void MeshInstance::Render()
{
	if ( ObjectMesh && InstanceOwner )
	{
		const auto& Verticies = ObjectMesh->GetVerticies();
		const auto& Indicies = ObjectMesh->GetIndicies();
		
		glUseProgram( CompiledShader );
		ApplyShaderUniforms();
		ApplyRenderSettings();
		ApplyTextures();

		switch ( ObjectMesh->GetVertexReadMode() )
		{
			case Mesh::VertexLoadingModes::Indexed:
				glDrawArrays( GL_TRIANGLES, 0, Verticies.size() );
				//glDrawElements( GL_TRIANGLES, Indicies.size(), GL_UNSIGNED_INT, 0 );
				break;
			case Mesh::VertexLoadingModes::Array:
				glDrawArrays( GL_TRIANGLES, 0, Verticies.size() );
				break;
			default:
				break;
		}

		glBindTexture( GL_TEXTURE_2D, 0 );
		glBindVertexArray( 0 );
	}
}
