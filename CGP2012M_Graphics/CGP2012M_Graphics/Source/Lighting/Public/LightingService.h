#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include <Application/Public/ApplicationService.h>

class LightSource;
class ApplicationState;
class LightingService : public ApplicationService
{

public:
	
	LightingService( ApplicationState* InAppState );

public:

	std::weak_ptr< LightSource > CreateNewLight( glm::vec3 Position, glm::vec4 Colour );
	glm::vec4 GetAmbientLight() const;
	std::vector<std::weak_ptr< LightSource > > GetDynamicLights() const; //returns copies
	int GetDynamicLightCount() const;

private:

	glm::vec3										LightingColour;
	float											AmbientIntensity;
	std::vector<std::weak_ptr< LightSource > >		DynamicLights;

};
