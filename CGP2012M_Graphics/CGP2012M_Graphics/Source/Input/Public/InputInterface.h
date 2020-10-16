#pragma once
#include <Input\Public\Input.h>

class IInputInterface
{
public:

	std::weak_ptr< InputHandler > InputHandlerWeakPtr; // REMOVE THIS im going to add a less hacky way of providing the handler

	void BindInput( const SDL_Keycode Key, std::function< void() > CallBack );
};