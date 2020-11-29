#include <Application/Public/ApplicationService.h>

ApplicationService::ApplicationService( ApplicationState* InApplicationState )
	: ApplicationStateInstance( InApplicationState )
{
}

ApplicationState* ApplicationService::GetApplicationState() const
{
	return ApplicationStateInstance;
}
