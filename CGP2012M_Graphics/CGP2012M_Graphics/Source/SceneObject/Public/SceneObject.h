#pragma once
#include <string>

#include <Transform/Public/Transform.h>

class ApplicationState;

class SceneObject
{
public:

	SceneObject( ApplicationState* AppStateStrongPtr );

	virtual void Render();

	Transform& GetTransform();
	std::string GetInstanceID() const;

protected:

	ApplicationState* const				AppState;

private:

	std::string							InstanceID; 
	Transform							LocalTransform;

};