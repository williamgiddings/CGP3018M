#include <Application/Public/ApplicationState.h>
#include <Camera/Public/Camera.h>
#include <Objects/Public/TestSpehre.h>
#include <SceneObject/Public/ScenePhysObject.h>

ApplicationState::ApplicationState()
	: InputHandlerServiceInstance( this )
	, MeshManagerServiceInstance( this )
	, ObjectManagerServiceInstance( this )
	, LightingServiceInstance( this )
	, Sphere()
	, SceneCamera()
	, SceneLight()
{
}

std::weak_ptr<Camera> ApplicationState::GetSceneCamera() const
{
	return SceneCamera;
}

void ApplicationState::StartGameState()
{
	SceneCamera = ObjectManagerServiceInstance.Instantiate<Camera>( Camera( this ) );
	SceneLight = LightingServiceInstance.CreateNewLight( glm::vec3(-2.0f, -1.0f, 0), glm::vec4( 0.9f, 0.9f, 0.9f, 1.0f ) );
	Sphere = ObjectManagerServiceInstance.Instantiate<TestSphere>( TestSphere( this ) );
	
	if ( auto SpherePtr = Sphere.lock() )
	{
		SpherePtr->SetScale( glm::vec3( 1.0f ) );
		SpherePtr->SetPosition( glm::vec3( 0.0f, 0.0f, 0.0f ) );
	}

	if ( auto SceneCameraPtr = SceneCamera.lock() )
	{
		SceneCameraPtr->SetCameraPosition( glm::vec3( 0.0f, 0.0f, 4.0f ) );
		SceneCameraPtr->SetCameraTarget( glm::vec3( 0.0f ) );
	}
}

void ApplicationState::TickGameState()
{
	ObjectManagerServiceInstance.TickSceneObjects();
}

InputHandlerService& ApplicationState::GetInputHandlerService()
{
	return InputHandlerServiceInstance;
}

MeshManagerService& ApplicationState::GetMeshManagerService()
{
	return MeshManagerServiceInstance;
}

ObjectManagerService& ApplicationState::GetObjectManagerService()
{
	return ObjectManagerServiceInstance;
}

LightingService & ApplicationState::GetLightingService()
{
	return LightingServiceInstance;
}
