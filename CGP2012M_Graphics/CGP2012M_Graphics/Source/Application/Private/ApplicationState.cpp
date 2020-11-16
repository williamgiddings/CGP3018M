#include <Application/Public/ApplicationState.h>
#include <SceneObject/Public/ScenePhysObject.h>

ApplicationState::ApplicationState()
	: InputHandlerServiceInstance()
	, MeshManagerServiceInstance()
{
}

void ApplicationState::StartGameState()
{
	std::shared_ptr<ScenePhysObject> Cube = ObjectManagerServiceInstance.Instantiate<ScenePhysObject>( ScenePhysObject( this, "sphere.obj" ) );
	if ( auto* CubePtr = Cube.get() )
	{
		CubePtr->SetScale( glm::vec3( 1.0f ) );
		//CubePtr->SetPosition( glm::vec3( -50.0f, 0, 0 ) );
	}

}

void ApplicationState::TickGameState()
{

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