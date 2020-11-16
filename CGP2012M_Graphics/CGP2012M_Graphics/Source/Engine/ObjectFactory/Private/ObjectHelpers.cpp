#include <Application/Public/ApplicationState.h>
#include <Engine/ObjectFactory/Public/ObjectHelpers.h>
#include <Engine/ObjectFactory/Public/ObjectManagerService.h>
#include <SceneObject/Public/SceneObject.h>

template<typename ObjectClass>
std::shared_ptr<ObjectClass> SpawnObject( ApplicationState * const AppState, SceneObject ObjectToSpawn )
{
	if ( AppState )
	{
		return AppState->GetObjectManagerService().Instantiate<ObjectClass>( ObjectToSpawn );
	}
	return nullptr;
}