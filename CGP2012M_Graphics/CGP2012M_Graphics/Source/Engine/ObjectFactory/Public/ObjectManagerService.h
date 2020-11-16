#pragma once
#include <memory>
#include <vector>

#include <SceneObject/Public/SceneObject.h>

using SceneObjectSharedPtr = std::shared_ptr< SceneObject >;

class ObjectManagerService
{
public:

	ObjectManagerService();

	template< typename ObjectClass >
	std::shared_ptr< ObjectClass> Instantiate( const ObjectClass InObject );
	
	void RenderSceneObjects();

private:

	std::vector< SceneObjectSharedPtr >		ObjectsInScene;

};

template<typename ObjectClass>
std::shared_ptr<ObjectClass> ObjectManagerService::Instantiate( const ObjectClass InObject )
{
	if ( std::is_base_of< SceneObject, ObjectClass >::value )
	{
		std::shared_ptr< ObjectClass > SpawnedObject( std::make_shared<ObjectClass>( InObject ) );
		ObjectsInScene.push_back( SpawnedObject );
		return SpawnedObject;
	}
	//Error here if the given ObjectClass is not derived from SceneObject
	return nullptr;
}
