#include <Application/Public/ApplicationState.h>
#include <SceneObject/Public/ScenePhysObject.h>

ApplicationState::ApplicationState()
	: InputHandlerServiceInstance()
	, MeshManagerServiceInstance()
{
}

void ApplicationState::StartGameState()
{
	std::shared_ptr<ScenePhysObject> Cube = ObjectManagerServiceInstance.Instantiate<ScenePhysObject>( ScenePhysObject( this, "cube.obj" ) );



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