#include <Application/Public/ApplicationState.h>
#include <Lighting/Public/LightSource.h>

LightSource::LightSource( ApplicationState* InAppState, glm::vec4 InLightColour )
	: SceneObject( InAppState )
	, LightColour( InLightColour )
{
}

bool LightSource::GetLightState() const
{
	return State;
}

glm::vec4 LightSource::GetLightColour() const
{
	return LightColour;
}
