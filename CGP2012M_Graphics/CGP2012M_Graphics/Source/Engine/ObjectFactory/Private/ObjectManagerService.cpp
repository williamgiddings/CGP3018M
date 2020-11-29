#include <Engine/ObjectFactory/Public/ObjectManagerService.h>

ObjectManagerService::ObjectManagerService( ApplicationState* InAppState )
	: ApplicationService( InAppState )
	, ObjectsInScene()
{
}

void ObjectManagerService::RenderSceneObjects()
{
	for ( auto SceneObjectShared : ObjectsInScene )
	{
		if ( auto* SceneObjectPtr = SceneObjectShared.get() )
		{
			SceneObjectPtr->Render();
		}
	}
}

void ObjectManagerService::TickSceneObjects()
{
	for ( auto SceneObjectShared : ObjectsInScene )
	{
		if ( auto* SceneObjectPtr = SceneObjectShared.get() )
		{
			SceneObjectPtr->Tick();
		}
	}
}