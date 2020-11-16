#ifndef GLEW_H
#define GLEW_H
#include "windows.h"


#include "SDL.h"
//#include "SDL_image.h"
//#include "SDL_mixer.h"
//#include "SDL_ttf.h"

#define GLM_FORCE_RADIANS // force glm to use radians

#include <GL/glew.h>

// ---------------------------------------------------------------------

#include <Application/Public/ApplicationWindow.h>

int main( int argc, char *argv[] )
{
	SDL_Init( SDL_INIT_EVERYTHING );

	ApplicationWindow Application;

	return Application.StartGameLoop();
}
#endif