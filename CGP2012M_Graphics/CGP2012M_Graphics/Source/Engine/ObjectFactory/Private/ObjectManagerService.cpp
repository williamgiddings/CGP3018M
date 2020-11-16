#include <Engine/ObjectFactory/Public/ObjectManagerService.h>

ObjectManagerService::ObjectManagerService()
	: ObjectsInScene()
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