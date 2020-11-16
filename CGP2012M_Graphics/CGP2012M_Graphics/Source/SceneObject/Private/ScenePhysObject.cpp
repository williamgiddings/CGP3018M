#include <Application/Public/ApplicationState.h>
#include <Engine/EngineEnvironment.h>
#include <Mesh/Public/MeshManagerService.h>
#include <SceneObject/Public/ScenePhysObject.h>

ScenePhysObject::ScenePhysObject( ApplicationState* AppStateStrongPtr, const char* MeshName )
	: SceneObject( AppStateStrongPtr )
	, ObjectMesh( this, LoadMesh( MeshName ) )
{
}

std::shared_ptr<Mesh> ScenePhysObject::LoadMesh( const char* MeshName )
{
	if ( AppState )
	{
		return AppState->GetMeshManagerService().GetMesh( MeshName );
	}
	return nullptr;
}

void ScenePhysObject::Render()
{
	ObjectMesh.Render();
}
