
#include <Input/Public/InputBinding.h>
#include <Input/Public/InputHandlerService.h>
#include <Input/Public/InputInterface.h>

InputHandlerService::InputHandlerService()
	: InputBindingMap()
{
}

InputBindingHandle InputHandlerService::BindInput( InputInterface* Binder, SDL_Keycode KeyCode, std::function< void() > Callback )
{
	auto BoundInput = InputBindingHandle( new InputBinding( Binder, KeyCode, Callback ) );
	FindOrCreateInputForKey( KeyCode ).push_back( BoundInput );
	return BoundInput;
}

void InputHandlerService::UnBindInput( InputBindingHandle Binding )
{
	auto Bindings = InputBindingMap.find( Binding->GetKey() );

	if ( Bindings != InputBindingMap.end() )
	{
		for ( unsigned i = 0; i < Bindings->second.size(); ++i )
		{
			Bindings->second.remove_if( 
				[ &Binding ]( const InputBindingHandle& In )
				{
					return In->GetInputOwner().lock() == Binding->GetInputOwner().lock();
				}
			);
		}
	}

	if ( Binding )
	{
		Binding->Invalidate();
	}
}

void InputHandlerService::PollInput()
{
	SDL_Event event;
	while ( SDL_PollEvent( &event ) )
	{
		switch ( event.type )
		{
		case SDL_KEYDOWN:
			CheckInput( event.key.keysym.sym );
			break;
		case SDL_KEYUP:
			//Key up
			break;
		}
	}
}

void InputHandlerService::CheckInput( const SDL_Keycode Key )
{
	auto Bindings = InputBindingMap.find( Key );

	if ( Bindings != InputBindingMap.end() )
	{
		for ( auto it = Bindings->second.begin(); it != Bindings->second.end(); ++it )
		{
			if ( auto InputBinding = ( *it ) )
			{
				if ( InputBinding->IsValid() )
				{
					InputBinding->Execute();
				}
			}
		}
	}
}

std::list<InputBindingHandle>& InputHandlerService::FindOrCreateInputForKey( const SDL_Keycode KeyCode )
{
	auto Bindings = InputBindingMap.find( KeyCode );

	if ( Bindings != InputBindingMap.end() )
	{
		return Bindings->second;
	}
	else
	{
		auto Value = InputBindingMap.emplace( std::pair< SDL_Keycode, std::list< InputBindingHandle > >( KeyCode, std::list< InputBindingHandle >() ) );
		return Value.first->second;
	}
}

// Add key checking!!

