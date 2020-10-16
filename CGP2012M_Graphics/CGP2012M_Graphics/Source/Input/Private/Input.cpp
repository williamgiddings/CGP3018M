
#include <Input\Public\Input.h>
#include <Input\Public\InputInterface.h>


InputBinding::InputBinding( IInputInterface* Instance, std::function< void() > Func )
	: InputOwner( std::make_shared<IInputInterface>( *Instance ) )
	, Callback( Func )
	, IsValid( true )
	, Key( SDLK_UNKNOWN )
{
}

void InputBinding::Invalidate()
{
	Callback = nullptr;
	IsValid = false;
	InputOwner.reset();
}

InputHandler::InputHandler()
	: InputBindingMap()
{
}

InputBindingSharedPtr InputHandler::BindInput( IInputInterface* Binder, SDL_Keycode KeyCode, std::function< void() > Callback )
{
	auto BoundInput = InputBindingSharedPtr( new InputBinding( Binder, Callback ) );
	FindOrCreateInputForKey( KeyCode ).push_back( BoundInput );
	return BoundInput;
}

void InputHandler::UnBindInput( InputBindingSharedPtr Binding )
{
	if ( Binding )
	{
		Binding->Invalidate();
	}
}

std::vector<InputBindingSharedPtr>& InputHandler::FindOrCreateInputForKey( const SDL_Keycode KeyCode )
{
	auto Bindings = InputBindingMap.find( KeyCode );

	if ( Bindings != InputBindingMap.end() )
	{
		return Bindings->second;
	}
	else
	{
		auto Value = InputBindingMap.emplace( std::pair< SDL_Keycode, std::vector< InputBindingSharedPtr > >( KeyCode, std::vector< InputBindingSharedPtr >() ) );
		return Value.first->second;
	}
}

// Add key checking!!

