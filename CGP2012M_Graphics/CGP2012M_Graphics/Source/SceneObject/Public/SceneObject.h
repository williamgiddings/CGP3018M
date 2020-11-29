#pragma once
#include <string>

#include <Transform/Public/Transform.h>

class ApplicationState;

class SceneObject : public Transform
{
public:

	SceneObject( ApplicationState* AppStateStrongPtr );

	virtual void Tick();
	virtual void Render();

	std::string GetInstanceID() const;
	ApplicationState* GetAppState() const;

protected:

	ApplicationState* const				AppState;
	std::string							InstanceID; 

};