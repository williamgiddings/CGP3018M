#pragma once

#include <SDL.h>
#include <functional>
#include <map>
#include <vector>
#include <memory>

class IInputInterface;
class InputBinding
{

public:

	explicit InputBinding( IInputInterface* Instance, std::function< void() > Func );
	void Invalidate();

private:

	std::function< void() > Callback;
	std::weak_ptr< IInputInterface > InputOwner;
	bool IsValid;
	SDL_Keycode Key;

};

using InputBindingSharedPtr = std::shared_ptr< InputBinding >;
class InputHandler
{

public:

	InputHandler();

	InputBindingSharedPtr BindInput( IInputInterface* Binder, SDL_Keycode KeyCode, std::function< void() > Callback );
	void UnBindInput( InputBindingSharedPtr Binding );

private:

	std::vector< InputBindingSharedPtr >& FindOrCreateInputForKey( const SDL_Keycode KeyCode );

private:

	std::map< SDL_Keycode, std::vector< InputBindingSharedPtr > > InputBindingMap;

};