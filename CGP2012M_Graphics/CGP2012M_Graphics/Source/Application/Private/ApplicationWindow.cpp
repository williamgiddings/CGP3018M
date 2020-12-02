#include <memory>

#include <Application/Public/ApplicationWindow.h>
#include <Engine/EngineEnvironment.h>
#include <Mesh/Public/Mesh.h>
#include <MeshParser/Public/OBJParser.h>


#include <Shader/Public/Shader.h>
ApplicationWindow* ApplicationWindow::WindowInstance;
ApplicationWindow::ApplicationWindow()
	: AppState()
	, ApplicationInputInterface()
	, QuitInput()
	, ColourInput()
	, SDLWindow( SDLWindow )
	, SDLContext( SDLContext )
	, BgColour()
	, WindowDimensions( 1920, 1080 )
	, WindowOpen( true )
{
	WindowInstance = this;
	SDLWindow = SDL_CreateWindow( "CGP3018M OpenGL Window", 100, 100, (int)WindowDimensions.x, (int)WindowDimensions.y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
	int major = 4, minor = 3;

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, major );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, minor );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDLContext = SDL_GL_CreateContext( SDLWindow );

	//GLEW initialise
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	SetBackGroundColour( 0.0f, 0.0f, 0.0f );
}

void ApplicationWindow::SetBackGroundColour( const float R, const float G, const float B )
{
	BgColour.r = R;
	BgColour.g = G;
	BgColour.b = B;
}

glm::vec2 ApplicationWindow::GetDimensions() const
{
	return WindowDimensions;
}

const ApplicationWindow* ApplicationWindow::GetWindow()
{
	return WindowInstance;
}

void ApplicationWindow::BindInputs()
{
	InputHandlerService& ApplicationInputHandler = AppState.GetInputHandlerService();

	QuitInput = ApplicationInputHandler.BindInput(
		&ApplicationInputInterface,
		SDLK_ESCAPE,
		std::function<void()>(
			[this]
			{
				CloseWindow();
			}
		)
	);

	ColourInput = ApplicationInputHandler.BindInput(
		&ApplicationInputInterface,
		SDLK_w,
		std::function<void()>(
			[this]
			{
				const float R = ( rand() % 100 ) / 100.0f;
				const float G = ( rand() % 100 ) / 100.0f;
				const float B = ( rand() % 100 ) / 100.0f;

				SetBackGroundColour( R, G, B );
			}
		)
	);
}

void ApplicationWindow::UnBindInputs()
{
	AppState.GetInputHandlerService().UnBindInput( QuitInput );
	AppState.GetInputHandlerService().UnBindInput( ColourInput );
}

int ApplicationWindow::StartGameLoop()
{
	BindInputs();

	AppState.StartGameState();

	Uint32 FrameStart;
	Uint32 FrameTime = 0;

	while ( WindowOpen )
	{
		FrameStart = SDL_GetTicks();

		Tick();
		Render();

		FrameTime = SDL_GetTicks() - FrameStart;

		if ( EngineEnvironment::TargetFrameTime > FrameTime )
		{
			SDL_Delay( EngineEnvironment::TargetFrameTime - FrameTime );
		}
	
	}

	return 0;
}

void ApplicationWindow::Tick()
{
	InputHandlerService& ApplicationInputHandler = AppState.GetInputHandlerService();

	ApplicationInputHandler.PollInput();
	AppState.TickGameState();
}

void ApplicationWindow::Render()
{
	glClearColor( BgColour.r, BgColour.g, BgColour.b, 1 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	AppState.GetObjectManagerService().RenderSceneObjects();
	
	SDL_GL_SwapWindow( SDLWindow );
}

void ApplicationWindow::CloseWindow()
{
	WindowOpen = false;
}

void ApplicationWindow::CleanUpApplication()
{
	UnBindInputs();
	SDL_GL_DeleteContext( SDLContext );
	SDL_Quit();
}

