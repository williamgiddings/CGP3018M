#include <Input\Public\InputInterface.h>

void IInputInterface::BindInput( const SDL_Keycode Key, std::function<void()> CallBack )
{
	if ( auto SharedInputHandler = std::make_shared<InputHandler>( InputHandlerWeakPtr ) )
	{
		SharedInputHandler->BindInput( this, Key, CallBack );
	}
}
