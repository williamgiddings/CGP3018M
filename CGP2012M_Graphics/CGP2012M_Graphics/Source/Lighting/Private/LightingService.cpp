#include <Application/Public/ApplicationState.h>
#include <Lighting/Public/LightSource.h>
#include <Lighting/Public/LightingService.h>

LightingService::LightingService( ApplicationState* InAppState )
	: ApplicationService( InAppState )
	, LightingColour( glm::vec3( 0.3f, 0.3f, 0.0f ) )
	, AmbientIntensity( 1.0f )
	, DynamicLights()
{
}

std::weak_ptr<LightSource> LightingService::CreateNewLight( glm::vec3 Position, glm::vec4 Colour )
{
	if ( auto* AppState = GetApplicationState() )
	{
		auto Light = AppState->GetObjectManagerService().Instantiate<LightSource>( LightSource( AppState, Colour) );
		Light->SetPosition( Position );
		DynamicLights.push_back( Light );
		return Light;
	}

	return std::weak_ptr<LightSource>();
}

glm::vec4 LightingService::GetAmbientLight() const
{
	return glm::vec4( LightingColour, AmbientIntensity );
}

std::vector<std::weak_ptr< LightSource > > LightingService::GetDynamicLights() const
{
	return DynamicLights;
}

int LightingService::GetDynamicLightCount() const
{
	int LightCount = 0;
	for ( auto Light : DynamicLights )
	{
		if ( Light.lock() )
		{
			LightCount++;
		}
	}
	return LightCount;
}

