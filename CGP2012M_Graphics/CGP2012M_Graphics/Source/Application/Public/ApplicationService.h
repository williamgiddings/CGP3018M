#pragma once
#include <memory>

class ApplicationState;
class ApplicationService
{

public:
	
	ApplicationService( ApplicationState* InApplicationState );

public:

	ApplicationState* GetApplicationState() const;

private:

	ApplicationState* ApplicationStateInstance;

};