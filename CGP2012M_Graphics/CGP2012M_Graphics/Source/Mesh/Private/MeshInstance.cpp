#include <glm/gtc/type_ptr.hpp>

#include <Application/Public/ApplicationState.h>
#include <Mesh/Public/MeshInstance.h>
#include <SceneObject/Public/ScenePhysObject.h>

MeshInstance::MeshInstance( ScenePhysObject* InInstanceOwner, const char* MeshName )
	: ObjectMesh()
	, ObjectMaterial()
	, RenderWireframe( false )
	, FlipUVs( false )
	, ClearDepth( true )
	, VertexDrawMode( MeshInstance::VertexDrawModes::Tris )
	, InstanceOwner( InInstanceOwner )
	, UniformBindings()
{
	LoadMesh( MeshName );
}

void MeshInstance::LoadMesh( const char* MeshName )
{
	if ( InstanceOwner )
	{
		if ( auto* AppState = InstanceOwner->GetAppState() )
		{
			ObjectMesh = AppState->GetMeshManagerService().GetMesh( MeshName );
		}
	}
}

void MeshInstance::SetRenderType( const VertexDrawModes DrawMode )
{
	VertexDrawMode = DrawMode;
}

void MeshInstance::ApplyShaderUniforms()
{
	if ( auto* MaterialPtr = ObjectMaterial.get() )
	{
		auto CompiledShader = MaterialPtr->GetCompiledShader();

		auto NormalMatrixBinding = glGetUniformLocation( CompiledShader, UniformBindings.NormalMatrixBinding.first );
		glUniformMatrix4fv( NormalMatrixBinding, 1, GL_FALSE, glm::value_ptr( UniformBindings.NormalMatrixBinding.second ) );

		auto TransformBinding = glGetUniformLocation( CompiledShader, UniformBindings.TransformBinding.first );
		glUniformMatrix4fv( TransformBinding, 1, GL_FALSE, glm::value_ptr( UniformBindings.TransformBinding.second ) );

		auto ProjectionMatrixBinding = glGetUniformLocation( CompiledShader, UniformBindings.ProjectionMatrixBinding.first );
		glUniformMatrix4fv( ProjectionMatrixBinding, 1, GL_FALSE, glm::value_ptr( UniformBindings.ProjectionMatrixBinding.second ) );

		auto ViewMatrixBinding = glGetUniformLocation( CompiledShader, UniformBindings.ViewMatrixBinding.first );
		glUniformMatrix4fv( ViewMatrixBinding, 1, GL_FALSE, glm::value_ptr( UniformBindings.ViewMatrixBinding.second ) );

		auto SceneLightCountBinding = glGetUniformLocation( CompiledShader, UniformBindings.SceneLightCount.first );
		glUniform1i( SceneLightCountBinding, UniformBindings.SceneLightCount.second );

		auto SceneLightAmbientIntensityBinding = glGetUniformLocation( CompiledShader, UniformBindings.SceneLightAmbient.first );
		glUniform4fv( SceneLightAmbientIntensityBinding, 1, glm::value_ptr( UniformBindings.SceneLightAmbient.second ) );

		ApplyLightingUniforms();
	}
}

void MeshInstance::ApplyLightingUniforms()
{
	if ( auto* MaterialPtr = ObjectMaterial.get() )
	{
		auto CompiledShader = MaterialPtr->GetCompiledShader();

		const char* DynamicLightUniformName = UniformBindings.SceneLights.first;
		for ( int i = 0; i < ( int ) UniformBindings.SceneLights.second.size(); ++i )
		{
			if ( auto LightPtr = UniformBindings.SceneLights.second[i].lock() )
			{
				const bool IsLightActive = LightPtr->GetLightState();

				std::stringstream UniformString;
				UniformString << DynamicLightUniformName << "[" << i << "].position";

				GLuint UniformLocation = glGetUniformLocation( CompiledShader, UniformString.str().c_str() );
				glUniform3fv( UniformLocation, 1, glm::value_ptr( LightPtr->GetPosition() ) );

				UniformString.str( "" );
				UniformString << DynamicLightUniformName << "[" << i << "].colour";
				glm::vec4 LightColour = IsLightActive ? LightPtr->GetLightColour() : glm::vec4( 0 );

				GLuint UniformColour = glGetUniformLocation( CompiledShader, UniformString.str().c_str() );
				glUniform4fv( UniformColour, 1, glm::value_ptr( LightColour ) );

				UniformString.str( "" );
			}
		}
	}
}

void MeshInstance::ApplyRenderSettings()
{
	if ( auto ObjectMeshPtr = ObjectMesh.lock() )
	{
		glEnable( GL_BLEND );
		glCullFace( GL_BACK );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable( GL_DEPTH_TEST );
		glDepthFunc( GL_LEQUAL );
		glBindVertexArray( ObjectMeshPtr->GetVertexArrayObject() );
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
	if ( auto* MaterialPtr = ObjectMaterial.get() )
	{
		MaterialPtr->BindTextureUniforms();
	}
}

void MeshInstance::Render()
{
	if ( auto ObjectMeshPtr = ObjectMesh.lock() )
	{
		if ( auto* MaterialPtr = ObjectMaterial.get() )
		{
			const auto& Verticies = ObjectMeshPtr->GetVerticies();
			const auto& Indicies = ObjectMeshPtr->GetIndicies();

			glUseProgram( MaterialPtr->GetCompiledShader() );
			ApplyShaderUniforms();
			ApplyTextures();
			ApplyRenderSettings();

			switch ( ObjectMeshPtr->GetVertexReadMode() )
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
		}
		
		glBindTexture( GL_TEXTURE_2D, 0 );
		glBindVertexArray( 0 );
	}
}

void MeshInstance::SetUniformBindings( const UniformBinding InBinding )
{
	UniformBindings = InBinding;
}

std::weak_ptr<Mesh> MeshInstance::GetSharedMesh() const
{
	return ObjectMesh;
}

std::weak_ptr<Material> MeshInstance::GetMaterial() const
{
	std::weak_ptr<Material> MaterialWeakPtr;

	if ( auto* MaterialStringPtr = ObjectMaterial.get() )
	{
		MaterialWeakPtr = std::weak_ptr<Material>( ObjectMaterial );
	}
	return MaterialWeakPtr;
}
