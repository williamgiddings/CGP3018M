#include <Input/Public/InputBinding.h>
#include <Input/Public/InputInterface.h>

InputBinding::InputBinding( InputInterface* Instance, SDL_Keycode Key, std::function< void() > Func )
	: InputOwner( std::make_shared<InputInterface>( *Instance ) )
	, Key( Key )
	, Callback( Func )
	, Valid( true )
{
}

void InputBinding::Invalidate()
{
	Callback = nullptr;
	Valid = false;
	InputOwner.reset();
}

SDL_Keycode InputBinding::GetKey()
{
	return Key;
}

std::weak_ptr<InputInterface> InputBinding::GetInputOwner()
{
	return InputOwner.lock();
}

void InputBinding::Execute()
{
	Callback();
}

bool InputBinding::IsValid() const
{
	return Valid;
}