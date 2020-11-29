#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Input/Public/InputHandlerService.h>
#include <Input/Public/InputInterface.h>
#include <Application/Public/ApplicationState.h>

class ApplicationWindow
{
public:

	ApplicationWindow();

	int StartGameLoop();
	void CloseWindow();
	void SetBackGroundColour( const float R, const float G , const float B );
	glm::vec2 GetDimensions() const;

	static const ApplicationWindow* GetWindow();

private:

	void Tick();
	void Render();
	void BindInputs();
	void UnBindInputs();
	void CleanUpApplication();

private:
	
	static ApplicationWindow*			WindowInstance;

	ApplicationState					AppState;
	InputInterface						ApplicationInputInterface;
	
	InputBindingHandle					QuitInput;
	InputBindingHandle					ColourInput;

	SDL_GLContext						SDLContext;
	SDL_Window*							SDLWindow;

	glm::vec3							BgColour;
	glm::vec2							WindowDimensions;
	bool								WindowOpen;
};
