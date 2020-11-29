#pragma once
#include <SDL.h>
#include <functional>
#include <map>
#include <list>
#include <memory>

#include <Application/Public/ApplicationService.h>

class InputBinding;
class InputInterface;

using InputBindingHandle = std::shared_ptr< InputBinding >;
class InputHandlerService : public ApplicationService
{
public:

	InputHandlerService( ApplicationState* InAppState );

	InputBindingHandle BindInput( InputInterface* Binder, SDL_Keycode KeyCode, std::function< void() > Callback );
	void UnBindInput( InputBindingHandle Binding );
	void PollInput();

private:

	void CheckInput( const SDL_Keycode Key );
	std::list< InputBindingHandle >& FindOrCreateInputForKey( const SDL_Keycode KeyCode );

private:

	std::map< SDL_Keycode, std::list< InputBindingHandle > > InputBindingMap;

};