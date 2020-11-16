#pragma once
#include <memory>

class ApplicationState;
class SceneObject;

static std::shared_ptr< SceneObject > SpawnObject( ApplicationState* const AppState, SceneObject ObjectToSpawn );

template< typename ObjectClass >
static std::shared_ptr< ObjectClass > SpawnObject( ApplicationState* const AppState );
