#include <Camera/Public/Camera.h>
#include <Application/Public/ApplicationWindow.h>

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera( ApplicationState* AppStateStrongPtr )
	: SceneObject( AppStateStrongPtr )
	, CameraTarget( 0.0f )
	, CameraViewMatrix( 0.0f )
	, CameraFOV( 65.0f )
	, CameraSpeed( 0.2f )
{
}

void Camera::SetCameraPosition( const glm::vec3 InPos )
{
	SetPosition( InPos );
}

void Camera::SetCameraTarget( const glm::vec3 LookTarget )
{
	CameraTarget = LookTarget;
}

void Camera::Tick()
{
	CameraViewMatrix = glm::lookAt( 
		GetPosition(),
		CameraTarget,
		Up 
	);
}

glm::mat4 Camera::GetViewMatrix() const
{
	return CameraViewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	glm::mat4 Perspective;

	if ( auto* Window = ApplicationWindow::GetWindow() )
	{
		glm::vec2 WindowDimensions = Window->GetDimensions();
		Perspective = glm::perspective( glm::radians( CameraFOV ), (float)WindowDimensions.x / (float)WindowDimensions.y, 0.01f, 100000.0f );
	}
	return Perspective;
}
