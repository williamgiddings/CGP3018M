#pragma once
#include <SDL.h>
#include <functional>
#include <memory>

class InputInterface;

class InputBinding
{

public:

	explicit InputBinding( InputInterface* Instance, SDL_Keycode Key, std::function< void() > Func );
	void Execute();
	void Invalidate();
	SDL_Keycode GetKey();
	std::weak_ptr<InputInterface> GetInputOwner();
	bool IsValid() const;

private:

	std::function< void() > Callback;
	std::weak_ptr< InputInterface > InputOwner;
	SDL_Keycode Key;
	bool Valid;

};