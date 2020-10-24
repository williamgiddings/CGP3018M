#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <Mesh/Primatives/Public/Triangle.h>
#include <Shader/Public/Shader.h>
#include <Input/Public/Input.h>
#include <Input/Public/InputInterface.h>

#ifndef GLEW_H
#define GLEW_H
#include "windows.h"

#include "SDL.h"
//#include "SDL_image.h"
//#include "SDL_mixer.h"
//#include "SDL_ttf.h"

// // - OpenGL Mathematics - https://glm.g-truc.net/
#define GLM_FORCE_RADIANS // force glm to use radians
// // NOTE: must do before including GLM headers
// // NOTE: GLSL uses radians, so will do the same, for consistency
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int GameLoop( SDL_Window* const win, SDL_GLContext& glcontext )
{
	IInputInterface ApplicationInputInterface;
	InputHandler InputHandler;
	
	bool windowOpen = true;

	InputBindingHandle QuitInput = InputHandler.BindInput(
		&ApplicationInputInterface,
		SDLK_ESCAPE,
		std::function<void()>(
			[&windowOpen]
			{
				windowOpen = false;
			}
		)
	);

	Triangle tri;

	//create shaders
	Shader vSh;
	Shader fSh;

	vSh.SetShaderProgram( Shader::ShaderType::Vertex, "shader" );
	fSh.SetShaderProgram( Shader::ShaderType::Fragment, "shader" );

	//create shader program, attach shaders together in the shader program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader( shaderProgram, vSh.GetCompiledShader() );
	glAttachShader( shaderProgram, fSh.GetCompiledShader() );
	glLinkProgram( shaderProgram );

	//delete shader source code pointers
	glDeleteShader( vSh.GetCompiledShader() );
	glDeleteShader( fSh.GetCompiledShader() );

	glm::vec3 BgColour;

	InputBindingHandle ColourInput = InputHandler.BindInput(
		&ApplicationInputInterface,
		SDLK_w,
		std::function<void()>(
			[&BgColour]
			{
				BgColour.r = ( rand() % 100 ) / 100.0f;
				BgColour.g = ( rand() % 100 ) / 100.0f;
				BgColour.b = ( rand() % 100 ) / 100.0f;
			}
		)
	);

	tri.setBuffers();

	while ( windowOpen )
	{
		InputHandler.PollInput();
		glClearColor( BgColour.r, BgColour.g, BgColour.b, 1 );
		glClear( GL_COLOR_BUFFER_BIT );
		glUseProgram( shaderProgram );
		glBindVertexArray( tri.VAO );

		glDrawArrays( GL_TRIANGLES, 0, 3 );
		glBindVertexArray( 0 );

		SDL_GL_SwapWindow( win );

	}

	InputHandler.UnBindInput( QuitInput );
	InputHandler.UnBindInput( ColourInput );

	SDL_GL_DeleteContext( glcontext );

	SDL_Quit();
	return 0;
}

int main(int argc, char *argv[]) 
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *win = SDL_CreateWindow("CGP3018M OpenGL Window", 100, 100, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	int major = 4, minor = 3;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE); 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create an OpenGL context associated with the window.
	SDL_GLContext glcontext = SDL_GL_CreateContext(win);

	//GLEW initialise
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	return GameLoop( win, glcontext );
}

#endif