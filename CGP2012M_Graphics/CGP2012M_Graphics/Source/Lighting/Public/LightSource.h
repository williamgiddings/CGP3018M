#pragma once
#include <glm/glm.hpp>

#include <SceneObject/Public/SceneObject.h>

class ApplicationState;
class LightSource : public SceneObject
{

public:

	LightSource( ApplicationState* InAppState, glm::vec4 InLightColour );

public:

	bool GetLightState() const;
	glm::vec4 GetLightColour() const;

private:

	glm::vec4	LightColour;
	bool		State;

};
