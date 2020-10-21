#pragma once

#include <SDL.h>
#include <functional>
#include <map>
#include <list>
#include <memory>

class IInputInterface;
class InputBinding
{

public:

	explicit InputBinding( IInputInterface* Instance, SDL_Keycode Key, std::function< void() > Func );
	void Execute();
	void Invalidate();
	SDL_Keycode GetKey();
	std::weak_ptr<IInputInterface> GetInputOwner();
	bool IsValid() const;

private:

	std::function< void() > Callback;
	std::weak_ptr< IInputInterface > InputOwner;
	SDL_Keycode Key;
	bool Valid;

};

using InputBindingHandle = std::shared_ptr< InputBinding >;
class InputHandler
{

public:

	InputHandler();

	InputBindingHandle BindInput( IInputInterface* Binder, SDL_Keycode KeyCode, std::function< void() > Callback );
	void UnBindInput( InputBindingHandle Binding );
	void PollInput();

private:

	void CheckInput( const SDL_Keycode Key );
	std::list< InputBindingHandle >& FindOrCreateInputForKey( const SDL_Keycode KeyCode );

private:

	std::map< SDL_Keycode, std::list< InputBindingHandle > > InputBindingMap;

};