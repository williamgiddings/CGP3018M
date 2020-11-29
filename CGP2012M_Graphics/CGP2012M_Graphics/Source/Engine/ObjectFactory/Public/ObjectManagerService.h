#pragma once
#include <memory>
#include <vector>

#include <Application/Public/ApplicationService.h>
#include <SceneObject/Public/SceneObject.h>

using SceneObjectSharedPtr = std::shared_ptr< SceneObject >;

class ObjectManagerService : public ApplicationService
{
public:

	ObjectManagerService( ApplicationState* InAppState );

public:

	template< typename ObjectClass >
	std::shared_ptr< ObjectClass> Instantiate( const ObjectClass InObject );
	
	void RenderSceneObjects();
	void TickSceneObjects();

private:

	std::vector< SceneObjectSharedPtr >		ObjectsInScene;

};

template<typename ObjectClass>
std::shared_ptr<ObjectClass> ObjectManagerService::Instantiate( const ObjectClass InObject )
{
	if ( std::is_base_of< SceneObject, ObjectClass >::value )
	{
		std::shared_ptr< ObjectClass > SpawnedObject( new ObjectClass( InObject ) );
		ObjectsInScene.push_back( SpawnedObject );
		return SpawnedObject;
	}
	//Error here if the given ObjectClass is not derived from SceneObject
	return nullptr;
}
