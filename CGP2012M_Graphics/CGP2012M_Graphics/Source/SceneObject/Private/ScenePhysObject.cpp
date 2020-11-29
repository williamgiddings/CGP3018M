#include <Application/Public/ApplicationState.h>
#include <Camera/Public/Camera.h>
#include <Engine/EngineEnvironment.h>
#include <Lighting/Public/LightingService.h>
#include <Material/Public/DiffuseMaterial.h>
#include <Mesh/Public/MeshManagerService.h>
#include <SceneObject/Public/ScenePhysObject.h>

ScenePhysObject::ScenePhysObject( ApplicationState* AppStateStrongPtr, const char* MeshName )
	: SceneObject( AppStateStrongPtr )
	, ObjectMesh( this, MeshName )
{
}

void ScenePhysObject::Render()
{
	ObjectMesh.SetUniformBindings( GetUniformBindings() );
	ObjectMesh.Render();
}

UniformBinding ScenePhysObject::GetUniformBindings()
{
	UniformBinding Bindings;

	const LightingService& Lighting = AppState->GetLightingService();
	glm::mat4 CameraViewMatrix;
	glm::mat4 CameraProjectionMatrix;
	glm::mat4 Normalmatrix = ( glm::mat3 )glm::transpose( glm::inverse( GetMatrix() ) );

	if ( auto SceneCameraPtr = AppState->GetSceneCamera().lock() )
	{
		CameraProjectionMatrix = SceneCameraPtr->GetProjectionMatrix();
		CameraViewMatrix = SceneCameraPtr->GetViewMatrix();
	}

	Bindings.NormalMatrixBinding = UniformPairMat4( "uNormalMatrix", Normalmatrix );
	Bindings.TransformBinding = UniformPairMat4( "uTransform", GetMatrix() );
	Bindings.ProjectionMatrixBinding = UniformPairMat4( "uProjection", CameraProjectionMatrix );
	Bindings.ViewMatrixBinding = UniformPairMat4( "uView", CameraViewMatrix );
	Bindings.SceneLightAmbient = UniformPairFloat4( "uAmbientLight", Lighting.GetAmbientLight() );
	Bindings.SceneLights = UniformPairLightArray( "uDynamicLights", Lighting.GetDynamicLights() );
	Bindings.SceneLightCount = UniformPairInt( "uLightCount", Lighting.GetDynamicLightCount() );

	return Bindings;
}